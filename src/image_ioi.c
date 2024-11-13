#include "image_io.h"
#include "bmp.h"
#include <stdio.h>

// Функция для чтения изображения из BMP файла
int read_image(const char *source_path, struct image *img) {
    FILE *input = fopen(source_path, "rb");
    if (!input) {
        perror("Не удалось открыть исходный файл");
        return 1;
    }

    enum read_status r_status = from_bmp(input, img);
    fclose(input);

    if (r_status != READ_OK) {
        fprintf(stderr, "Ошибка при чтении BMP изображения\n");
        return 1;
    }

    return 0;
}

// Функция для записи изображения в BMP файл
int write_image(const char *dest_path, const struct image *img) {
    FILE *output = fopen(dest_path, "wb");
    if (!output) {
        perror("Не удалось открыть выходной файл");
        return 1;
    }

    enum write_status w_status = to_bmp(output, img);
    fclose(output);

    if (w_status != WRITE_OK) {
        fprintf(stderr, "Ошибка при записи BMP изображения\n");
        return 1;
    }

    return 0;
}
