#include "transform.h"
#include <stdlib.h>

struct image rotate_image(struct image *source) {
    struct image rotated = create_image(source->height, source->width);

    if (!rotated.data)
        return rotated;

    for (uint64_t y = 0; y < source->height; y++) {
        for (uint64_t x = 0; x < source->width; x++) {
            uint64_t x_new = y;
            uint64_t y_new = (rotated.height - 1) - x;
            *image_pixel(&rotated, x_new, y_new) = *image_pixel(source, x, y);
        }
    }

    return rotated;
}