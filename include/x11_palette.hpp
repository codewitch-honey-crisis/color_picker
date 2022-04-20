#include <gfx_core.hpp>
#include <gfx_pixel.hpp>
#include <gfx_color_cpp14.hpp>
namespace gfx {
    template<typename MappedPixelType> 
    struct x11_palette {
        static_assert(!MappedPixelType::template has_channel_names<channel_name::index>::value,"Mapped pixel must not be indexed");
    private:
        constexpr static gfx_result index_to_mapped(int idx,MappedPixelType* result) {
            switch(idx) {
                case 0: *result = color<MappedPixelType>::alice_blue; return gfx_result::success;
                case 1: *result = color<MappedPixelType>::antique_white; return gfx_result::success;
                case 2: *result = color<MappedPixelType>::aqua; return gfx_result::success;
                case 3: *result = color<MappedPixelType>::aquamarine; return gfx_result::success;
                case 4: *result = color<MappedPixelType>::azure; return gfx_result::success;
                case 5: *result = color<MappedPixelType>::beige; return gfx_result::success;
                case 6: *result = color<MappedPixelType>::bisque; return gfx_result::success;
                case 7: *result = color<MappedPixelType>::black; return gfx_result::success;
                case 8: *result = color<MappedPixelType>::blanched_almond; return gfx_result::success;
                case 9: *result = color<MappedPixelType>::blue; return gfx_result::success;
                case 10: *result = color<MappedPixelType>::blue_violet; return gfx_result::success;
                case 11: *result = color<MappedPixelType>::brown; return gfx_result::success;
                case 12: *result = color<MappedPixelType>::burly_wood; return gfx_result::success;
                case 13: *result = color<MappedPixelType>::cadet_blue; return gfx_result::success;
                case 14: *result = color<MappedPixelType>::chartreuse; return gfx_result::success;
                case 15: *result = color<MappedPixelType>::chocolate; return gfx_result::success;
                case 16: *result = color<MappedPixelType>::coral; return gfx_result::success;
                case 17: *result = color<MappedPixelType>::cornflower_blue; return gfx_result::success;
                case 18: *result = color<MappedPixelType>::cornsilk; return gfx_result::success;
                case 19: *result = color<MappedPixelType>::crimson; return gfx_result::success;
                case 20: *result = color<MappedPixelType>::cyan; return gfx_result::success;
                case 21: *result = color<MappedPixelType>::dark_blue; return gfx_result::success;
                case 22: *result = color<MappedPixelType>::dark_cyan; return gfx_result::success;
                case 23: *result = color<MappedPixelType>::dark_goldenrod; return gfx_result::success;
                case 24: *result = color<MappedPixelType>::dark_gray; return gfx_result::success;
                case 25: *result = color<MappedPixelType>::dark_green; return gfx_result::success;
                case 26: *result = color<MappedPixelType>::dark_khaki; return gfx_result::success;
                case 27: *result = color<MappedPixelType>::dark_magenta; return gfx_result::success;
                case 28: *result = color<MappedPixelType>::dark_olive_green; return gfx_result::success;
                case 29: *result = color<MappedPixelType>::dark_orange; return gfx_result::success;
                case 30: *result = color<MappedPixelType>::dark_orchid; return gfx_result::success;
                case 31: *result = color<MappedPixelType>::dark_red; return gfx_result::success;
                case 32: *result = color<MappedPixelType>::dark_salmon; return gfx_result::success;
                case 33: *result = color<MappedPixelType>::dark_sea_green; return gfx_result::success;
                case 34: *result = color<MappedPixelType>::dark_slate_blue; return gfx_result::success;
                case 35: *result = color<MappedPixelType>::dark_slate_gray; return gfx_result::success;
                case 36: *result = color<MappedPixelType>::dark_turquoise; return gfx_result::success;
                case 37: *result = color<MappedPixelType>::dark_violet; return gfx_result::success;
                case 38: *result = color<MappedPixelType>::deep_pink; return gfx_result::success;
                case 39: *result = color<MappedPixelType>::deep_sky_blue; return gfx_result::success;
                case 40: *result = color<MappedPixelType>::dim_gray; return gfx_result::success;
                case 41: *result = color<MappedPixelType>::dodger_blue; return gfx_result::success;
                case 42: *result = color<MappedPixelType>::firebrick; return gfx_result::success;
                case 43: *result = color<MappedPixelType>::floral_white; return gfx_result::success;
                case 44: *result = color<MappedPixelType>::forest_green; return gfx_result::success;
                case 45: *result = color<MappedPixelType>::fuchsia; return gfx_result::success;
                case 46: *result = color<MappedPixelType>::gainsboro; return gfx_result::success;
                case 47: *result = color<MappedPixelType>::ghost_white; return gfx_result::success;
                case 48: *result = color<MappedPixelType>::gold; return gfx_result::success;
                case 49: *result = color<MappedPixelType>::goldenrod; return gfx_result::success;
                case 50: *result = color<MappedPixelType>::gray; return gfx_result::success;
                case 51: *result = color<MappedPixelType>::green; return gfx_result::success;
                case 52: *result = color<MappedPixelType>::green_yellow; return gfx_result::success;
                case 53: *result = color<MappedPixelType>::honeydew; return gfx_result::success;
                case 54: *result = color<MappedPixelType>::hot_pink; return gfx_result::success;
                case 55: *result = color<MappedPixelType>::indian_red; return gfx_result::success;
                case 56: *result = color<MappedPixelType>::indigo; return gfx_result::success;
                case 57: *result = color<MappedPixelType>::ivory; return gfx_result::success;
                case 58: *result = color<MappedPixelType>::khaki; return gfx_result::success;
                case 59: *result = color<MappedPixelType>::lavender; return gfx_result::success;
                case 60: *result = color<MappedPixelType>::lavender_blush; return gfx_result::success;
                case 61: *result = color<MappedPixelType>::lawn_green; return gfx_result::success;
                case 62: *result = color<MappedPixelType>::lemon_chiffon; return gfx_result::success;
                case 63: *result = color<MappedPixelType>::light_blue; return gfx_result::success;
                case 64: *result = color<MappedPixelType>::light_coral; return gfx_result::success;
                case 65: *result = color<MappedPixelType>::light_cyan; return gfx_result::success;
                case 66: *result = color<MappedPixelType>::light_goldenrod_yellow; return gfx_result::success;
                case 67: *result = color<MappedPixelType>::light_green; return gfx_result::success;
                case 68: *result = color<MappedPixelType>::light_gray; return gfx_result::success;
                case 69: *result = color<MappedPixelType>::light_pink; return gfx_result::success;
                case 70: *result = color<MappedPixelType>::light_salmon; return gfx_result::success;
                case 71: *result = color<MappedPixelType>::light_sea_green; return gfx_result::success;
                case 72: *result = color<MappedPixelType>::light_sky_blue; return gfx_result::success;
                case 73: *result = color<MappedPixelType>::light_slate_gray; return gfx_result::success;
                case 74: *result = color<MappedPixelType>::light_steel_blue; return gfx_result::success;
                case 75: *result = color<MappedPixelType>::light_yellow; return gfx_result::success;
                case 76: *result = color<MappedPixelType>::lime; return gfx_result::success;
                case 77: *result = color<MappedPixelType>::lime_green; return gfx_result::success;
                case 78: *result = color<MappedPixelType>::linen; return gfx_result::success;
                case 79: *result = color<MappedPixelType>::magenta; return gfx_result::success;
                case 80: *result = color<MappedPixelType>::maroon; return gfx_result::success;
                case 81: *result = color<MappedPixelType>::medium_aquamarine; return gfx_result::success;
                case 82: *result = color<MappedPixelType>::medium_blue; return gfx_result::success;
                case 83: *result = color<MappedPixelType>::medium_orchid; return gfx_result::success;
                case 84: *result = color<MappedPixelType>::medium_purple; return gfx_result::success;
                case 85: *result = color<MappedPixelType>::medium_sea_green; return gfx_result::success;
                case 86: *result = color<MappedPixelType>::medium_slate_blue; return gfx_result::success;
                case 87: *result = color<MappedPixelType>::medium_spring_green; return gfx_result::success;
                case 88: *result = color<MappedPixelType>::medium_turquoise; return gfx_result::success;
                case 89: *result = color<MappedPixelType>::medium_violet_red; return gfx_result::success;
                case 90: *result = color<MappedPixelType>::midnight_blue; return gfx_result::success;
                case 91: *result = color<MappedPixelType>::mint_cream; return gfx_result::success;
                case 92: *result = color<MappedPixelType>::misty_rose; return gfx_result::success;
                case 93: *result = color<MappedPixelType>::moccasin; return gfx_result::success;
                case 94: *result = color<MappedPixelType>::navajo_white; return gfx_result::success;
                case 95: *result = color<MappedPixelType>::navy; return gfx_result::success;
                case 96: *result = color<MappedPixelType>::old_lace; return gfx_result::success;
                case 97: *result = color<MappedPixelType>::olive; return gfx_result::success;
                case 98: *result = color<MappedPixelType>::olive_drab; return gfx_result::success;
                case 99: *result = color<MappedPixelType>::orange; return gfx_result::success;
                case 100: *result = color<MappedPixelType>::orange_red; return gfx_result::success;
                case 101: *result = color<MappedPixelType>::orchid; return gfx_result::success;
                case 102: *result = color<MappedPixelType>::pale_goldenrod; return gfx_result::success;
                case 103: *result = color<MappedPixelType>::pale_green; return gfx_result::success;
                case 104: *result = color<MappedPixelType>::pale_turquoise; return gfx_result::success;
                case 105: *result = color<MappedPixelType>::pale_violet_red; return gfx_result::success;
                case 106: *result = color<MappedPixelType>::papaya_whip; return gfx_result::success;
                case 107: *result = color<MappedPixelType>::peach_puff; return gfx_result::success;
                case 108: *result = color<MappedPixelType>::peru; return gfx_result::success;
                case 109: *result = color<MappedPixelType>::pink; return gfx_result::success;
                case 110: *result = color<MappedPixelType>::plum; return gfx_result::success;
                case 111: *result = color<MappedPixelType>::powder_blue; return gfx_result::success;
                case 112: *result = color<MappedPixelType>::purple; return gfx_result::success;
                case 113: *result = color<MappedPixelType>::red; return gfx_result::success;
                case 114: *result = color<MappedPixelType>::rosy_brown; return gfx_result::success;
                case 115: *result = color<MappedPixelType>::royal_blue; return gfx_result::success;
                case 116: *result = color<MappedPixelType>::saddle_brown; return gfx_result::success;
                case 117: *result = color<MappedPixelType>::salmon; return gfx_result::success;
                case 118: *result = color<MappedPixelType>::sandy_brown; return gfx_result::success;
                case 119: *result = color<MappedPixelType>::sea_green; return gfx_result::success;
                case 120: *result = color<MappedPixelType>::sea_shell; return gfx_result::success;
                case 121: *result = color<MappedPixelType>::sienna; return gfx_result::success;
                case 122: *result = color<MappedPixelType>::silver; return gfx_result::success;
                case 123: *result = color<MappedPixelType>::sky_blue; return gfx_result::success;
                case 124: *result = color<MappedPixelType>::slate_blue; return gfx_result::success;
                case 125: *result = color<MappedPixelType>::slate_gray; return gfx_result::success;
                case 126: *result = color<MappedPixelType>::snow; return gfx_result::success;
                case 127: *result = color<MappedPixelType>::spring_green; return gfx_result::success;
                case 128: *result = color<MappedPixelType>::steel_blue; return gfx_result::success;
                case 129: *result = color<MappedPixelType>::tan; return gfx_result::success;
                case 130: *result = color<MappedPixelType>::teal; return gfx_result::success;
                case 131: *result = color<MappedPixelType>::thistle; return gfx_result::success;
                case 132: *result = color<MappedPixelType>::tomato; return gfx_result::success;
                case 133: *result = color<MappedPixelType>::turquoise; return gfx_result::success;
                case 134: *result = color<MappedPixelType>::violet; return gfx_result::success;
                case 135: *result = color<MappedPixelType>::wheat; return gfx_result::success;
                case 136: *result = color<MappedPixelType>::white; return gfx_result::success;
                case 137: *result = color<MappedPixelType>::white_smoke; return gfx_result::success;
                case 138: *result = color<MappedPixelType>::yellow; return gfx_result::success;
                case 139: *result = color<MappedPixelType>::yellow_green; return gfx_result::success;
                default: *result = MappedPixelType(); return gfx_result::invalid_argument;
            }
        }
    public:
        using type = x11_palette;
        constexpr static const size_t size = 140;
        using pixel_type = pixel<channel_traits<channel_name::index,8,0,size-1>>;
        using mapped_pixel_type = MappedPixelType;
        constexpr static const bool writable = false;
        gfx_result map(pixel_type pixel,mapped_pixel_type* mapped_pixel) const {
            return index_to_mapped(pixel.channel<channel_name::index>(),mapped_pixel);
        }
        gfx_result nearest(mapped_pixel_type mapped_pixel,pixel_type* pixel) const {
            
            if(nullptr==pixel) {
                return gfx_result::invalid_argument;
            }
            mapped_pixel_type mpx;
            gfx_result r = index_to_mapped(0,&mpx);
            if(gfx_result::success!=r) {
                return r;
            }
            double least = mpx.difference(mapped_pixel);
            if(0.0==least) {
                pixel->native_value = 0;
                return gfx_result::success;
            }
            int ii=0;
            for(int i = 1;i<size;++i) {
                r=index_to_mapped(i,&mpx);
                if(gfx_result::success!=r) {
                    return r;
                }
                double cmp = mpx.difference(mapped_pixel);
                if(0.0==cmp) {
                    ii=i;
                    least = 0.0;
                    break;
                }
                if(cmp<least) {
                    least = cmp;
                    ii=i;
                }
            }
            pixel->channel<channel_name::index>(ii);
            return gfx_result::success;
        }
    };
}