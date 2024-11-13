#include "image.h"
#include <stdlib.h>

#include "image.h"
#include <stdlib.h>
#include <limits.h>  // Для проверки переполнения

struct image create_image(uint64_t width, uint64_t height) {
    struct image img;

    // Проверка на переполнение при умножении
    if (width == 0 || height == 0 || width > UINT64_MAX / height) {
        img.width = 0;
        img.height = 0;
        img.data = NULL;
        return img;
    }

    img.width = width;
    img.height = height;
    img.data = calloc(width * height, sizeof(struct pixel));  // Выделение памяти и инициализация нулями
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

struct pixel *image_pixel(const struct image *img, uint64_t x, uint64_t y) {
    if (x >= img->width || y >= img->height) {
        return NULL; // Вернуть NULL, если координаты вне пределов изображения
    }
    return &img->data[y * img->width + x];
}