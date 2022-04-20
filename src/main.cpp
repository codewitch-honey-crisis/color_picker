// Arduino ESP32 headers
#include <Arduino.h>
#include <SPIFFS.h>
// bus framework header
#include <tft_io.hpp>
// driver header
#include <ili9341.hpp>
// touch header
#include <xpt2046.hpp>
// gfx for C++14 header
#include <gfx_cpp14.hpp>
// our x11 stuff
#include "x11_palette.hpp"
#include "x11_names.hpp"
// import the namespace for the drivers
using namespace arduino;
// and for GFX
using namespace gfx;

// both devices share the SPI bus:
#define HOST VSPI

// wiring is as follows for the touch and display
// MOSI 23
// MISO 19
// SCLK 18
// VCC 3.3v
// see below for additional pins:
#define LCD_CS 5
#define LCD_DC 2
#define LCD_RST 4
#define LCD_BL 14

#define TOUCH_CS 15
// you may need to change this to 1 if your screen is upside down
#define LCD_ROTATION 3
// if you don't see any backlight, or any display 
// try changing this to false
#define LCD_BL_HIGH true

// use the default pins for the SPI bus
using bus_t = tft_spi_ex<HOST,LCD_CS,23,19,18,SPI_MODE0,false>;
// set up the display
using lcd_t = ili9341<LCD_DC,LCD_RST,LCD_BL,bus_t,LCD_ROTATION,LCD_BL_HIGH>;
// set up the touch driver
using touch_t = xpt2046<TOUCH_CS>;

// declare the display
lcd_t lcd;
// declare the touch. The touch takes a reference to an SPIClass
// However, devices that share a bus must share the same instance.
// Always retrieving the SPIClass from spi_container ensures the same
// instance for the same host (requires the htcw_tft_io lib)
// Since the touch and the LCD share a bus, we want to use
// the same instance. spi_container<HOST>::instance() retrieves that
// in a cross platform manner.
touch_t touch(spi_container<HOST>::instance());

// easy access to the X11 colors for our display
using color_t = color<typename lcd_t::pixel_type>;
// easy access to our X11 palette mapped to 24-bit HSV
using x11_t = x11_palette<hsv_pixel<24>>;

// you can try one of the other fonts if you like.
const char* font_path =  "/Ubuntu.ttf"; //"/Telegrama.otf"; // "/Bungee.otf";
const char* font_name = font_path+1;
uint8_t* font_buffer;
size_t font_buffer_len;

float current_hue;
  
// calibrates the screen, optionally writing the calibration file to SPIFFS
void calibrate(bool write=true) {
  touch.initialize();
  File file;
  if(write) {
    file = SPIFFS.open("/calibration","wb");
  }
  int16_t values[8];
  uint16_t x,y;
  srect16 sr(0,0,15,15);
  ssize16 ssr(8,8);
  // top left
  lcd.fill(lcd.bounds(),color_t::white);
  draw::filled_rectangle(lcd,ssr.bounds().offset(sr.top_left()),color_t::sky_blue);
  draw::filled_ellipse(lcd,sr,color_t::sky_blue);
  while(!touch.calibrate_touch(&x,&y)) delay(1);
  values[0]=x;values[1]=y;
  if(write) {
    file.write((uint8_t*)&x,2);
    file.write((uint8_t*)&y,2);
  }
  lcd.fill((rect16)sr,color_t::white);
  delay(1000); // debounce
  
  // top right
  sr=srect16(0,0,15,15);
  sr.offset_inplace(lcd.dimensions().width-sr.width(),0);
  draw::filled_rectangle(lcd,ssr.bounds().offset(sr.x1+sr.width()/2,sr.y1),color_t::sky_blue);
  draw::filled_ellipse(lcd,sr,color_t::sky_blue);
  while(!touch.calibrate_touch(&x,&y)) delay(1);
  values[2]=x;values[3]=y;
  if(write) {
    file.write((uint8_t*)&x,2);
    file.write((uint8_t*)&y,2);
  }
  lcd.fill((rect16)sr,color_t::white);
  delay(1000); // debounce
  
  // bottom right
  sr=srect16(0,0,15,15);
  sr.offset_inplace(lcd.dimensions().width-sr.width(),lcd.dimensions().height-sr.height());
  draw::filled_rectangle(lcd,ssr.bounds().offset(sr.x1+sr.width()/2,sr.y1+sr.height()/2),color_t::sky_blue);
  draw::filled_ellipse(lcd,sr,color_t::sky_blue);
  while(!touch.calibrate_touch(&x,&y)) delay(1);
  values[4]=x;values[5]=y;
  if(write) {
    file.write((uint8_t*)&x,2);
    file.write((uint8_t*)&y,2);
  }
  lcd.fill((rect16)sr,color_t::white);
  delay(1000); // debounce

  // bottom left
  sr=srect16(0,0,15,15);
  sr.offset_inplace(0,lcd.dimensions().height-sr.height());
  lcd.fill(lcd.bounds(),color_t::white);
  draw::filled_rectangle(lcd,ssr.bounds().offset(sr.x1,sr.y1+sr.height()/2),color_t::sky_blue);
  draw::filled_ellipse(lcd,sr,color_t::sky_blue);
  while(!touch.calibrate_touch(&x,&y)) delay(1);
  values[6]=x;values[7]=y;
  if(write) {
    file.write((uint8_t*)&x,2);
    file.write((uint8_t*)&y,2);
  }
  lcd.fill((rect16)sr,color_t::white);
  delay(1000); // debounce
  touch.calibrate(lcd.dimensions().width,lcd.dimensions().height,values);
  if(write) {
    file.close();
  }
}
// read the calibration from SPIFFS
bool read_calibration() {
  if(SPIFFS.exists("/calibration")) {
    File file = SPIFFS.open("/calibration","rb");
    int16_t values[8];
    uint16_t x,y;
    for(int i = 0;i<8;i+=2) {
      if(2!=file.readBytes((char*)&x,2)) { file.close(); return false; }
      if(2!=file.readBytes((char*)&y,2)) { file.close(); return false; }
      values[i]=x;
      values[i+1]=y;
    }
    file.close();
    return touch.calibrate(lcd.dimensions().width,lcd.dimensions().height,values);
  }
  return false;
}
// draw a 90deg linear gradient from HSV(0%,100%,100%) to HSV(100%,100%,100%)
void draw_hue_bar(rect16 rect) {
  int w = (float)rect.width()/(float)((hsv_pixel<24>::channel_by_name<channel_name::H>::max-hsv_pixel<24>::channel_by_name<channel_name::H>::min)+1);
  if(w==0)
    w=1;

  for(int x = rect.left();x <= rect.right(); ++x) {
    hsv_pixel<24> px(true,(((float)(x-rect.left()))/(rect.width()-1)),1,1);
    draw::filled_rectangle(lcd,srect16(x,rect.top(),x+w-1,rect.bottom()),px);
  }
}
// draw the color match bar (exact and nearest x11 color)
void draw_color(hsv_pixel<24> color) {
  draw::filled_rectangle(lcd,srect16(0,140,159,159),color);
  x11_t pal;
  typename x11_t::pixel_type px;
  pal.nearest(color,&px);
  pal.map(px,&color);
  draw::filled_rectangle(lcd,srect16(160,140,319,159),color);

}
// draw the name of the color
void draw_color_name(hsv_pixel<24> color) {
  x11_t pal;
  typename x11_t::pixel_type ipx;
  pal.nearest(color,&ipx);
  const char* name = x11_names[ipx.template channel<0>()];
  // reconstitute our font stream from PSRAM
  const_buffer_stream cbs(font_buffer,font_buffer_len);
  open_font fnt;
  // attempt to open the font (already checked in setup)
  open_font::open(&cbs,&fnt);
  float scale = fnt.scale(30);
  ssize16 fsz = fnt.measure_text({32767,32767},{0,0},name,scale).inflate(2,2);
  srect16 tr = fsz.bounds().center({0,160,319,208});
  draw::filled_rectangle(lcd,srect16(0,160,319,208),color_t::white);
  draw::text(lcd,tr,{0,0},name,fnt,scale,color_t::black);
}

void draw_frame(int hue) {
  // draw a linear gradient on the HSV axis, where h is fixed at "hue"
  // and S and V are along the Y and X axes, respectively
  hsv_pixel<24> px(true,(((float)hue)/(lcd.dimensions().width-1)),1,1);
  auto px2 = px;
  // batching is the fastest way
  auto b = draw::batch(lcd,srect16(0,0,319,139));
  for(int y = 0;y<140;++y) {
    px2.template channelr<channel_name::S>(((double)y)/139.0);
    for(int x = 0;x<320;++x) {
      px2.template channelr<channel_name::V>(((double)x)/319.0);
      b.write(px2);
    }
  }
  // commit what we wrote
  b.commit();
  // draw the color bar
  draw_color(px);
  // draw the color name
  draw_color_name(px);
}
void setup() {
  Serial.begin(115200);
  SPIFFS.begin(true);
  lcd.initialize();
  touch.initialize();

  File file = SPIFFS.open(font_path,"rb");
  if(!file)  {
    Serial.printf("Asset %s not found. Halting.",font_name);
    while(true) delay(1000);
  }
  // get the file length
  file.seek(0,fs::SeekMode::SeekEnd);
  size_t len = file.position();
  file.seek(0);
  if(len==0) {
    Serial.printf("Asset %s not found. Halting.",font_name);
    while(true) delay(1000);
  }
  // allocate the buffer
  font_buffer = (uint8_t*)ps_malloc(len);
  if(!font_buffer)  {
    Serial.printf("Unable to allocate PSRAM for asset %s. Halting.",font_name);
    while(true) delay(1000);
  }
  // copy the file into the buffer
  file.readBytes((char*)font_buffer,len);
  // don't need the file anymore
  file.close();
  font_buffer_len = len;
  // test the font to make sure it's good (avoiding checks later)
  // first wrap the buffer w/ a stream
  const_buffer_stream cbs(font_buffer,font_buffer_len);
  open_font fnt;
  // attempt to open the font
  gfx_result r=open_font::open(&cbs,&fnt);
  if(r!=gfx_result::success) {
    Serial.printf("Unable to load asset %s. Halting.",font_name);
    while(true) delay(1000);
  }

  if(!read_calibration() || !touch.calibrated()) {
    calibrate(true);
  }
  current_hue = 0;
  // draw the hue bar at the bottom
  draw_hue_bar({0,210,319,239});
  // draw the initial frame 
  draw_frame(0);
}


void loop() {
  uint16_t x=0,y=0;
  // touched?
  if(touch.calibrated_xy(&x,&y)) {
    // hue bar?
    if(y>=210) {
      current_hue = ((double)x)/319.0;
      draw_frame(x);
    } else if(y<140) { // gradient area
      double s = ((double)y)/139.0;
      double v = ((double)x)/319.0;
      // get our HSV pixel
      hsv_pixel<24> px(true,current_hue,s,v);
      // update the screen with it
      draw_color(px);
      draw_color_name(px);
    }
  }
}