#include "bmp.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define BMP_PADDING 4

// Функция чтения строки изображения BMP
static int read_bmp_row(FILE *in, uint8_t *row_data, size_t bmp_row_size) {
    if (fread(row_data, 1, bmp_row_size, in) != bmp_row_size) {
        return -1;
    }
    return 0;
}

// Функция записи строки изображения BMP
static int write_bmp_row(FILE *out, const uint8_t *row_data, size_t row_size, size_t padding) {
    if (fwrite(row_data, 1, row_size, out) != row_size) {
        return -1;
    }
    uint8_t padding_bytes[BMP_PADDING] = {0, 0, 0, 0};
    if (fwrite(padding_bytes, 1, padding, out) != padding) {
        return -1;
    }
    return 0;
}

enum read_status from_bmp(FILE *in, struct image *img) {
    if (!in || !img) return READ_INVALID_HEADER;

    struct bmp_header header;
    if (fread(&header, sizeof(struct bmp_header), 1, in) != 1)
        return READ_IO_ERROR;

    if (header.bfType != BMP_SIGNATURE)
        return READ_INVALID_SIGNATURE;

    if (header.biBitCount != BMP_BPP)
        return READ_INVALID_BITS;

    int32_t width = header.biWidth;
    int32_t height = header.biHeight;
    size_t abs_width = (size_t) (width < 0 ? -width : width);
    size_t abs_height = (size_t) (height < 0 ? -height : height);

    // Проверка на переполнение при выделении памяти
    if (abs_width == 0 || abs_height == 0 || abs_height > SIZE_MAX / abs_width) {
        return READ_INVALID_HEADER;
    }

    *img = create_image(abs_width, abs_height);
    if (!img->data) {
        return READ_MEMORY_ERROR;
    }

    // Вычисление размера строки с учетом выравнивания
    size_t pixel_row_size = abs_width * sizeof(struct pixel);
    size_t row_padding = (BMP_PADDING - (pixel_row_size % BMP_PADDING)) % BMP_PADDING;
    size_t bmp_row_size = pixel_row_size + row_padding;

    int is_top_down = (height < 0);

    if (fseek(in, (long) header.bOffBits, SEEK_SET) != 0) {
        destroy_image(img);
        return READ_IO_ERROR;
    }

    uint8_t *row_data = malloc(bmp_row_size);
    if (!row_data) {
        destroy_image(img);
        return READ_MEMORY_ERROR;
    }

    for (size_t y = 0; y < abs_height; y++) {
        size_t row = is_top_down ? y : (abs_height - 1 - y);
        if (read_bmp_row(in, row_data, bmp_row_size) != 0) {
            free(row_data);
            destroy_image(img);
            return READ_IO_ERROR;
        }
        struct pixel *row_ptr = image_pixel(img, 0, row);
        memcpy(row_ptr, row_data, pixel_row_size);
    }

    free(row_data);

    return READ_OK;
}

enum write_status to_bmp(FILE *out, const struct image *img) {
    if (!out || !img) return WRITE_ERROR;

    struct bmp_header header = {0};
    header.bfType = BMP_SIGNATURE;
    header.bOffBits = sizeof(struct bmp_header);
    header.biSize = 40;

    if (img->width > INT32_MAX || img->height > INT32_MAX) {
        return WRITE_ERROR; // Image dimensions are too large
    }

    header.biWidth = (int32_t) img->width;
    header.biHeight = (int32_t) img->height;
    header.biPlanes = 1;
    header.biBitCount = BMP_BPP;
    header.biCompression = 0;

    uint32_t row_size = (img->width * sizeof(struct pixel) + BMP_PADDING - 1) & ~(BMP_PADDING - 1);
    uint32_t padding = row_size - img->width * sizeof(struct pixel);
    header.biSizeImage = row_size * img->height;
    header.bfileSize = header.bOffBits + header.biSizeImage;

    if (fwrite(&header, sizeof(struct bmp_header), 1, out) != 1)
        return WRITE_ERROR;

    for (uint32_t y = 0; y < img->height; y++) {
        uint32_t row = img->height - 1 - y;
        if (write_bmp_row(out, (const uint8_t *) image_pixel(img, 0, row), img->width * sizeof(struct pixel),
                          padding) != 0) {
            return WRITE_ERROR;
        }
    }

    return WRITE_OK;
}
