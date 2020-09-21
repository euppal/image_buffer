//
//  image_buffer_grayscale.h
//  image_buffer
//

#ifndef image_buffer_grayscale_h
#define image_buffer_grayscale_h

#include <stdbool.h>
#include "image_buffer.h"

void write_grayscale_pixel(
    struct image_buffer* buffer,
    image_buffer_int v
);

void write_grayscale_line(
    struct image_buffer* buffer,
    image_buffer_int v,
    image_buffer_dimensions dest_x,
    image_buffer_dimensions dest_y
);

void write_grayscale_region(
    struct image_buffer* buffer,
    image_buffer_int v,
    image_buffer_dimensions end_x,
    image_buffer_dimensions end_y
);

void write_grayscale_circle(
    struct image_buffer* buffer,
    image_buffer_int v,
    image_buffer_dimensions radius
);

#endif /* image_buffer_grayscale_h */
