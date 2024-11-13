#ifndef IMAGE_IO_H
#define IMAGE_IO_H

#include "image.h"

// Прототипы функций для работы с изображениями
int read_image(const char *source_path, struct image *img);
int write_image(const char *dest_path, const struct image *img);

#endif // IMAGE_IO_H
