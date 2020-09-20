//
//  image_buffer.c
//  image_buffer
//

#include "image_buffer.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

// MARK: General Functions

void init_buffer(
    struct image_buffer* buffer,
    image_buffer_dimensions width,
    image_buffer_dimensions height,
    image_format format
) {
    buffer->_width = width;
    buffer->_height = height;
    buffer->_format = format;
    buffer->_x = 0;
    buffer->_y = 0;
    buffer->_data = (image_buffer_int**)calloc(sizeof(image_buffer_int*), height); // allocate `height` pointers
    for (image_buffer_dimensions r = 0; r < height; r++) {
        buffer->_data[r] = (image_buffer_int*)calloc(sizeof(image_buffer_int) * format, width); // allocate each pointer
    }
}

void free_buffer(
    const struct image_buffer* buffer
) {
    for (image_buffer_dimensions r = 0; r < buffer->_height; r++) {
        free(buffer->_data[r]);
    }
    free(buffer->_data);
}

void save_buffer(
    const struct image_buffer* buffer,
    const char* dest
) {

    FILE* img = fopen(dest, "wb");
    switch (buffer->_format) {
        case image_format_grayscale: {
            fputs("P2\n", img);
            break;
        }
        case image_format_rgb: {
            fputs("P3\n", img);
            break;
        }
    }
    
    fprintf(img, "%ld %ld\n", buffer->_width, buffer->_height);
    
    fputs("255\n", img);
    for (image_buffer_dimensions y = 0; y < buffer->_height; y++) {
        const image_buffer_int* row_pixels = buffer->_data[y];
        for (image_buffer_dimensions x = 0; x < buffer->_width * buffer->_format; x++) {
            fprintf(img, "%d ", row_pixels[x]);
        }
        fputc('\n', img);
    }
    fclose(img);
}

inline void pixel_cursor(
    struct image_buffer* buffer,
    image_buffer_dimensions x,
    image_buffer_dimensions y
) {
    buffer->_x = x;
    buffer->_y = y;
}

// MARK: RGB Functions

void write_rgb_pixel(
    struct image_buffer* buffer,
    image_buffer_int r,
    image_buffer_int g,
    image_buffer_int b
) {
    image_buffer_int* row_pixels = buffer->_data[buffer->_y];
    row_pixels[buffer->_x * 3] = r;
    row_pixels[buffer->_x * 3 + 1] = g;
    row_pixels[buffer->_x * 3 + 2] = b;
}

void write_rgb_line(
    struct image_buffer* buffer,
    image_buffer_int r,
    image_buffer_int g,
    image_buffer_int b,
    image_buffer_dimensions dest_x,
    image_buffer_dimensions dest_y
) {
    float x0 = (float)buffer->_x;
    float y0 = (float)buffer->_y;
    float x1 = (float)dest_x;
    float y1 = (float)dest_y;
    float deltax = x1 - x0;
    float deltay = y1 - y0;
    if (fabsf(deltax) > fabsf(deltay)) {
        if (deltax < 0.0f) {
            float tx, ty;
            tx = x1; ty = y1;
            x1 = x0; y1 = y0;
            x0 = tx; y0 = ty;
        }
        float deltaerr = fabsf(deltay / deltax);
        float error = 0.0f;
        image_buffer_dimensions y = y0;
        const image_buffer_dimensions new_x1 = (image_buffer_dimensions)x1;
        for (image_buffer_dimensions x = x0; x <= new_x1; x++) {
            pixel_cursor(buffer, x, buffer->_height - y - 1);
            write_rgb_pixel(buffer, r, g, b);
            error += deltaerr;
            if (error >= 0.5) {
                y += deltay < 0.0f ? -1 : 1;
                error -= 1.0f;
            }
        }
    } else {
        if (y1 < y0) {
            float tx, ty;
            tx = x1; ty = y1;
            x1 = x0; y1 = y0;
            x0 = tx; y0 = ty;
        }
        deltax = x1 - x0;
        deltay = y1 - y0;
        float deltaerr = fabsf(deltax / deltay);
        float error = 0.0f;
        image_buffer_dimensions x = x0;
        const image_buffer_dimensions new_y1 = (image_buffer_dimensions)y1;
        for (image_buffer_dimensions y = y0; y <= (image_buffer_dimensions)y1; y++) {
            pixel_cursor(buffer, x, buffer->_height - y - 1);
            write_rgb_pixel(buffer, r, g, b);
            error += deltaerr;
            if (error >= 0.5) {
                x += deltax < 0 ? -1 : 1;
                error -= 1.0f;
            }
        }
    }
}

void write_rgb_region(
    struct image_buffer* buffer,
    image_buffer_int r,
    image_buffer_int g,
    image_buffer_int b,
    image_buffer_dimensions end_x,
    image_buffer_dimensions end_y
) {
    image_buffer_dimensions min_x, min_y, max_x, max_y;
    min_x = min(buffer->_x, end_x);
    min_y = min(buffer->_y, end_y);
    max_x = max(buffer->_x, end_x);
    max_y = max(buffer->_y, end_y);
    
    for (image_buffer_dimensions row = min_y; row < max_y; row++) {
        image_buffer_int* row_pixels = buffer->_data[row];
        for (image_buffer_dimensions col = min_x; col < max_x; col += 3) {
            row_pixels[col] = r;
            row_pixels[col + 1] = g;
            row_pixels[col + 2] = b;
        }
    }
}

// MARK: Grayscale Functions

void write_grayscale_pixel(
    struct image_buffer* buffer,
    image_buffer_int v
) {
    buffer->_data[buffer->_y][buffer->_x] = v;
}

void write_grayscale_line(
    struct image_buffer* buffer,
    image_buffer_int v,
    image_buffer_dimensions dest_x,
    image_buffer_dimensions dest_y
) {
    float x0 = (float)buffer->_x;
    float y0 = (float)buffer->_y;
    float x1 = (float)dest_x;
    float y1 = (float)dest_y;
    float deltax = x1 - x0;
    float deltay = y1 - y0;
    if (fabsf(deltax) > fabsf(deltay)) {
        if (deltax < 0.0f) {
            float tx, ty;
            tx = x1; ty = y1;
            x1 = x0; y1 = y0;
            x0 = tx; y0 = ty;
        }
        float deltaerr = fabsf(deltay / deltax);
        float error = 0.0f;
        image_buffer_dimensions y = y0;
        for (image_buffer_dimensions x = x0; x <= x1; ++x) {
            pixel_cursor(buffer, x, buffer->_height - y);
            write_grayscale_pixel(buffer, v);
            error += deltaerr;
            if (error >= 0.5) {
                y += deltay < 0.0f ? -1 : 1;
                error -= 1.0f;
            }
        }
    } else {
        if (y1 < y0) {
            float tx, ty;
            tx = x1; ty = y1;
            x1 = x0; y1 = y0;
            x0 = tx; y0 = ty;
        }
        deltax = x1 - x0;
        deltay = y1 - y0;
        float deltaerr = fabsf(deltax / deltay);
        float error = 0.0f;
        size_t x = x0;
        for (size_t y = y0; y <= y1; ++y) {
            pixel_cursor(buffer, x, buffer->_height - y);
            write_grayscale_pixel(buffer, v);
            error += deltaerr;
            if (error >= 0.5) {
                x += deltax < 0 ? -1 : 1;
                error -= 1.0f;
            }
        }
    }
}

void write_grayscale_region(
    struct image_buffer* buffer,
    image_buffer_int v,
    image_buffer_dimensions end_x,
    image_buffer_dimensions end_y
) {
    image_buffer_dimensions min_x, min_y, max_x, max_y;
    min_x = min(buffer->_x, end_x);
    min_y = min(buffer->_y, end_y);
    max_x = max(buffer->_x, end_x);
    max_y = max(buffer->_y, end_y);
    
    for (image_buffer_dimensions row = min_y; row < max_y; row++) {
        image_buffer_int* row_pixels = buffer->_data[row];
        for (image_buffer_dimensions col = min_x; col < max_x; col++) {
            row_pixels[col] = v;
        }
    }
}
