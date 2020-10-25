//
//  image_buffer_rgb.h
//  image_buffer
//


#ifndef image_buffer_rgb_h
#define image_buffer_rgb_h

#include "image_buffer.h"

void write_rgb_pixel(
    struct image_buffer* buffer,
    image_buffer_int r,
    image_buffer_int g,
    image_buffer_int b
);

void write_rgb_line(
    struct image_buffer* buffer,
    image_buffer_int r,
    image_buffer_int g,
    image_buffer_int b,
    image_buffer_dimensions dest_x,
    image_buffer_dimensions dest_y
);

void write_rgb_region(
    struct image_buffer* buffer,
    image_buffer_int r,
    image_buffer_int g,
    image_buffer_int b,
    image_buffer_dimensions end_x,
    image_buffer_dimensions end_y
);

void write_wrgb_pixel(
    struct image_buffer* buffer,
    image_buffer_int r,
    image_buffer_int g,
    image_buffer_int b
);

void write_wrgb_line(
    struct image_buffer* buffer,
    image_buffer_int r,
    image_buffer_int g,
    image_buffer_int b,
    image_buffer_dimensions dest_x,
    image_buffer_dimensions dest_y
);

void write_wrgb_region(
    struct image_buffer* buffer,
    image_buffer_int r,
    image_buffer_int g,
    image_buffer_int b,
    image_buffer_dimensions end_x,
    image_buffer_dimensions end_y
);

#endif /* image_buffer_rgb_h */
