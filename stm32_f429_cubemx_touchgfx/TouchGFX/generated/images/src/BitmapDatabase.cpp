// 4.15.0 0xab39606b
// Generated by imageconverter. Please, do not edit!

#include <BitmapDatabase.hpp>
#include <touchgfx/Bitmap.hpp>

extern const unsigned char image_blue_buttons_round_edge_small[]; // BITMAP_BLUE_BUTTONS_ROUND_EDGE_SMALL_ID = 0, Size: 170x60 pixels
extern const unsigned char image_blue_buttons_round_edge_small_pressed[]; // BITMAP_BLUE_BUTTONS_ROUND_EDGE_SMALL_PRESSED_ID = 1, Size: 170x60 pixels
extern const unsigned char image_blue_clocks_backgrounds_clock_standard_background[]; // BITMAP_BLUE_CLOCKS_BACKGROUNDS_CLOCK_STANDARD_BACKGROUND_ID = 2, Size: 233x243 pixels
extern const unsigned char image_blue_clocks_hands_clock_standard_hour_hand[]; // BITMAP_BLUE_CLOCKS_HANDS_CLOCK_STANDARD_HOUR_HAND_ID = 3, Size: 15x61 pixels
extern const unsigned char image_blue_clocks_hands_clock_standard_minute_hand[]; // BITMAP_BLUE_CLOCKS_HANDS_CLOCK_STANDARD_MINUTE_HAND_ID = 4, Size: 15x77 pixels
extern const unsigned char image_blue_clocks_hands_clock_standard_second_hand[]; // BITMAP_BLUE_CLOCKS_HANDS_CLOCK_STANDARD_SECOND_HAND_ID = 5, Size: 7x86 pixels
extern const unsigned char image_blue_togglebars_toggle_round_large_button_off[]; // BITMAP_BLUE_TOGGLEBARS_TOGGLE_ROUND_LARGE_BUTTON_OFF_ID = 6, Size: 128x38 pixels
extern const unsigned char image_blue_togglebars_toggle_round_large_button_on[]; // BITMAP_BLUE_TOGGLEBARS_TOGGLE_ROUND_LARGE_BUTTON_ON_ID = 7, Size: 128x38 pixels

const touchgfx::Bitmap::BitmapData bitmap_database[] =
{
    { image_blue_buttons_round_edge_small, 0, 170, 60, 11, 4, 148, (uint8_t)(touchgfx::Bitmap::ARGB8888) >> 3, 50, (uint8_t)(touchgfx::Bitmap::ARGB8888) & 0x7 },
    { image_blue_buttons_round_edge_small_pressed, 0, 170, 60, 11, 4, 148, (uint8_t)(touchgfx::Bitmap::ARGB8888) >> 3, 50, (uint8_t)(touchgfx::Bitmap::ARGB8888) & 0x7 },
    { image_blue_clocks_backgrounds_clock_standard_background, 0, 233, 243, 43, 42, 147, (uint8_t)(touchgfx::Bitmap::ARGB8888) >> 3, 149, (uint8_t)(touchgfx::Bitmap::ARGB8888) & 0x7 },
    { image_blue_clocks_hands_clock_standard_hour_hand, 0, 15, 61, 3, 6, 9, (uint8_t)(touchgfx::Bitmap::ARGB8888) >> 3, 43, (uint8_t)(touchgfx::Bitmap::ARGB8888) & 0x7 },
    { image_blue_clocks_hands_clock_standard_minute_hand, 0, 15, 77, 3, 6, 9, (uint8_t)(touchgfx::Bitmap::ARGB8888) >> 3, 59, (uint8_t)(touchgfx::Bitmap::ARGB8888) & 0x7 },
    { image_blue_clocks_hands_clock_standard_second_hand, 0, 7, 86, 2, 2, 3, (uint8_t)(touchgfx::Bitmap::ARGB8888) >> 3, 81, (uint8_t)(touchgfx::Bitmap::ARGB8888) & 0x7 },
    { image_blue_togglebars_toggle_round_large_button_off, 0, 128, 38, 13, 1, 102, (uint8_t)(touchgfx::Bitmap::ARGB8888) >> 3, 36, (uint8_t)(touchgfx::Bitmap::ARGB8888) & 0x7 },
    { image_blue_togglebars_toggle_round_large_button_on, 0, 128, 38, 13, 1, 102, (uint8_t)(touchgfx::Bitmap::ARGB8888) >> 3, 36, (uint8_t)(touchgfx::Bitmap::ARGB8888) & 0x7 }
};

namespace BitmapDatabase
{
const touchgfx::Bitmap::BitmapData* getInstance()
{
    return bitmap_database;
}

uint16_t getInstanceSize()
{
    return (uint16_t)(sizeof(bitmap_database) / sizeof(touchgfx::Bitmap::BitmapData));
}
}