//
//  image_buffer.h
//  image_buffer
//

#ifndef image_buffer_h
#define image_buffer_h

typedef int image_buffer_int;
typedef long image_buffer_dimensions;

typedef enum {
    image_format_grayscale = 1,
    image_format_rgb = 3,
} image_format;

struct image_buffer {
    image_buffer_dimensions _width;
    image_buffer_dimensions _height;
    image_format _format;
    
    image_buffer_dimensions _x;
    image_buffer_dimensions _y;
    
    image_buffer_int** _data;
};

void init_buffer(
    struct image_buffer* buffer,
    image_buffer_dimensions width,
    image_buffer_dimensions height,
    image_format format
);

void free_buffer(
    const struct image_buffer* buffer
);

void save_buffer(
    const struct image_buffer* buffer,
    const char* dest
);

void pixel_cursor(
    struct image_buffer* buffer,
    image_buffer_dimensions x,
    image_buffer_dimensions y
);

#include "image_buffer_rgb.h"
#include "image_buffer_grayscale.h"

#endif /* image_buffer_h */
