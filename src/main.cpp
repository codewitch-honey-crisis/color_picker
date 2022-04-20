#include <Arduino.h>
#include <SPIFFS.h>
#include <tft_io.hpp>
#include <ili9341.hpp>
#include <gfx_cpp14.hpp>
#include <xpt2046.hpp>
#include "x11_palette.hpp"
using namespace arduino;
using namespace gfx;

#define HOST VSPI

#define LCD_CS 5
#define LCD_DC 2
#define LCD_RST 4
#define LCD_BL 22
#define LCD_ROTATION 3
#define LCD_BL_HIGH true

#define TOUCH_CS 15

using bus_t = tft_spi<HOST,LCD_CS>;
using lcd_t = ili9341<LCD_DC,LCD_RST,LCD_BL,bus_t,LCD_ROTATION,LCD_BL_HIGH>;
using touch_t = xpt2046<TOUCH_CS>;
using color_t = color<typename lcd_t::pixel_type>;
using x11_t = x11_palette<hsv_pixel<24>>;

const char* x11_names[] = {
  "alice blue",
  "antique white",
  "aqua",
  "aquamarine",
  "azure",
  "beige",
  "bisque",
  "black",
  "blanched almond",
  "blue",
  "blue violet",
  "brown",
  "burly wood",
  "cadet blue",
  "chartreuse",
  "chocolate",
  "coral",
  "cornflower blue",
  "cornsilk",
  "crimson",
  "cyan",
  "dark blue",
  "dark cyan",
  "dark goldenrod",
  "dark gray",
  "dark green",
  "dark khaki",
  "dark magenta",
  "dark olive green",
  "dark orange",
  "dark orchid",
  "dark red",
  "dark salmon",
  "dark sea green",
  "dark slate blue",
  "dark slate gray",
  "dark turquoise",
  "dark violet",
  "deep pink",
  "deep sky blue",
  "dim gray",
  "dodger blue",
  "firebrick",
  "floral white",
  "forest green",
  "fuchsia",
  "gainsboro",
  "ghost white",
  "gold",
  "goldenrod",
  "gray",
  "green",
  "green yellow",
  "honeydew",
  "hot pink",
  "indian red",
  "indigo",
  "ivory",
  "khaki",
  "lavender",
  "lavender blush",
  "lawn green",
  "lemon chiffon",
  "light blue",
  "light coral",
  "light cyan",
  "light goldenrod yellow",
  "light green",
  "light gray",
  "light pink",
  "light salmon",
  "light sea green",
  "light sky blue",
  "light slate gray",
  "light steel blue",
  "light yellow",
  "lime",
  "lime green",
  "linen",
  "magenta",
  "maroon",
  "medium aquamarine",
  "medium blue",
  "medium orchid",
  "medium purple",
  "medium sea green",
  "medium slate blue",
  "medium spring green",
  "medium turquoise",
  "medium violet red",
  "midnight blue",
  "mint cream",
  "misty rose",
  "moccasin",
  "navajo white",
  "navy",
  "old lace",
  "olive",
  "olive drab",
  "orange",
  "orange red",
  "orchid",
  "pale goldenrod",
  "pale green",
  "pale turquoise",
  "pale violet red",
  "papaya whip",
  "peach puff",
  "peru",
  "pink",
  "plum",
  "powder blue",
  "purple",
  "red",
  "rosy brown",
  "royal blue",
  "saddle brown",
  "salmon",
  "sandy brown",
  "sea green",
  "sea shell",
  "sienna",
  "silver",
  "sky blue",
  "slate blue",
  "slate gray",
  "snow",
  "spring green",
  "steel blue",
  "tan",
  "teal",
  "thistle",
  "tomato",
  "turquoise",
  "violet",
  "wheat",
  "white",
  "white smoke",
  "yellow",
  "yellow green"
};

const char* font_path =  "/Ubuntu.ttf"; //"/Telegrama.otf"; // "/Bungee.otf";
const char* font_name = font_path+1;
uint8_t* font_buffer;
size_t font_buffer_len;

lcd_t lcd;
touch_t touch(spi_container<HOST>::instance());

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
  lcd.fill(lcd.bounds(),color_t::white);
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
  lcd.fill(lcd.bounds(),color_t::white);
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
  lcd.fill(lcd.bounds(),color_t::white);
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
  lcd.fill(lcd.bounds(),color_t::white);
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

void draw_hue_bar(rect16 rect) {
  int w = (float)rect.width()/(float)((hsv_pixel<24>::channel_by_name<channel_name::H>::max-hsv_pixel<24>::channel_by_name<channel_name::H>::max)+1);
  if(w==0)
    w=1;

  for(int x = rect.left();x <= rect.right(); ++x) {
    hsv_pixel<24> px(true,(((float)(x-rect.left()))/(rect.width()-1)),1,1);
    draw::filled_rectangle(lcd,srect16(x,rect.top(),x+w-1,rect.bottom()),px);
  }
}
void draw_color(hsv_pixel<24> color) {
  draw::filled_rectangle(lcd,srect16(0,140,159,159),color);
  x11_t pal;
  typename x11_t::pixel_type px;
  pal.nearest(color,&px);
  pal.map(px,&color);
  draw::filled_rectangle(lcd,srect16(160,140,319,159),color);

}
void draw_color_name(hsv_pixel<24> color) {
  x11_t pal;
  typename x11_t::pixel_type ipx;
  pal.nearest(color,&ipx);
  const char* name = x11_names[ipx.template channel<0>()];
  const_buffer_stream cbs(font_buffer,font_buffer_len);
  open_font fnt;
  // attempt to open the font
  open_font::open(&cbs,&fnt);
  float scale = fnt.scale(30);
  ssize16 fsz = fnt.measure_text({32767,32767},{0,0},name,scale).inflate(2,2);
  srect16 tr = fsz.bounds().center({0,160,319,208});
  draw::filled_rectangle(lcd,srect16(0,160,319,208),color_t::white);
  draw::text(lcd,tr,{0,0},name,fnt,scale,color_t::black);
}

void draw_frame(int hue) {
  hsv_pixel<24> px(true,(((float)hue)/(lcd.dimensions().width-1)),1,1);
  auto px2 = px;
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
  draw_color(px);
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
  read_calibration();
  current_hue = 0;
  draw_hue_bar({0,210,319,239});
  draw_frame(0);
}


void loop() {
  uint16_t x=0,y=0;
  if(touch.calibrated_xy(&x,&y)) {
    if(y>=210) {
      current_hue = ((double)x)/319.0;
      draw_frame(x);
    } else if(y<140) {
      double s = ((double)y)/139.0;
      double v = ((double)x)/319.0;
      hsv_pixel<24> px(true,current_hue,s,v);
      draw_color(px);
      draw_color_name(px);
    }
  }
}