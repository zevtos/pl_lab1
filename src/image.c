#include "image.h"
#include <stdlib.h>

struct image create_image(size_t width, size_t height) {
    struct image img;
    img.width = width;
    img.height = height;
    img.data = malloc(width * height * sizeof(struct pixel));
    if (!img.data) {
        img.width = 0;
        img.height = 0;
    }
    return img;
}

void destroy_image(struct image *img) {
    if (img && img->data) {
        free(img->data);
        img->data = NULL;
        img->width = 0;
        img->height = 0;
    }
}