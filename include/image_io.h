#ifndef IMAGE_IO_H
#define IMAGE_IO_H

#include "image.h"

// Чтение изображения из файла
int read_image(const char *source_path, struct image *img);

// Запись изображения в файл
int write_image(const char *dest_path, const struct image *img);

#endif // IMAGE_IO_H
