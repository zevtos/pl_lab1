#ifndef IMAGE_H
#define IMAGE_H

#include <stdint.h>
#include "pixel.h"

#define IMAGE_PIXEL(img, x, y) ((img).data[(y) * (img).width + (x)])

struct image {
    uint64_t width;
    uint64_t height;
    struct pixel *data;
};

struct image create_image(uint64_t width, uint64_t height);

void destroy_image(struct image *img);

static inline struct pixel *image_pixel(struct image *img, size_t x, size_t y) {
    return &img->data[y * img->width + x];
}


#endif
