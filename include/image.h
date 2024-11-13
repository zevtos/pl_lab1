#ifndef IMAGE_H
#define IMAGE_H

#include <stdint.h>
#include <stddef.h>
#include "pixel.h"

// Определение структуры изображения
struct image {
    uint64_t width;
    uint64_t height;
    struct pixel *data;
};

// Создание изображения
struct image create_image(uint64_t width, uint64_t height);

// Уничтожение изображения
void destroy_image(struct image *img);

// Доступ к пикселям изображения (безопасная версия)
struct pixel *image_pixel(const struct image *img, uint64_t x, uint64_t y);

#endif // IMAGE_H
