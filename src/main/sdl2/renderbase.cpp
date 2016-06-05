#include "renderbase.hpp"
#include <iostream>

RenderBase::RenderBase()
{
    surface       = NULL;
    screen_pixels = NULL;

    orig_width  = 0;
    orig_height = 0;
}

// Setup screen size
bool RenderBase::sdl_screen_size()
{
    if (orig_width == 0 || orig_height == 0)
    {
	SDL_DisplayMode info;

	SDL_GetCurrentDisplayMode(0, &info);
        
        orig_width  = info.w; 
        orig_height = info.h;
    }

    scn_width  = orig_width;
    scn_height = orig_height;

    return true;
}

// See: SDL_PixelFormat
#define CURRENT_RGB() (r << Rshift) | (g << Gshift) | (b << Bshift);

void RenderBase::convert_palette(uint32_t adr, uint32_t r, uint32_t g, uint32_t b)
{
    adr >>= 1;

    r = r * 255 / 31;
    g = g * 255 / 31;
    b = b * 255 / 31;

    rgb[adr] = CURRENT_RGB();
      
    // Create shadow / highlight colours at end of RGB array
    // The resultant values are the same as MAME
    r = r * 202 / 256;
    g = g * 202 / 256;
    b = b * 202 / 256;
        
    rgb[adr + S16_PALETTE_ENTRIES] =
    rgb[adr + (S16_PALETTE_ENTRIES * 2)] = CURRENT_RGB();
}

void RenderBase::convert_pixels_to_rgb(int width, int height, uint16_t* source_pixels, uint32_t* converted_pixels_rbg) {
    for (int i = 0; i < (width * height); i++)
        *(converted_pixels_rbg++) = rgb[*(source_pixels++) & ((S16_PALETTE_ENTRIES * 3) - 1)];
}

void RenderBase::convert_pixels_to_greyscale(int width, int height, uint16_t* source_pixels, uint32_t* converted_pixels_greyscale) {
    for (int i = 0; i < (width * height); i++) {
        uint32_t rgb_value = rgb[*(source_pixels++) & ((S16_PALETTE_ENTRIES * 3) - 1)];
        uint32_t blue = ((rgb_value & 0xFF0000) >> 16);
        uint32_t green = ((rgb_value & 0xFF00) >> 8);
        uint32_t red = ((rgb_value & 0xFF));
        // http://stackoverflow.com/questions/596216/formula-to-determine-brightness-of-rgb-color?rq=1
        uint32_t greyscale_value = (red + red + red + blue + blue + green + green + green) >> 3;
        *(converted_pixels_greyscale++) = greyscale_value;
    }
}