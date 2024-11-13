#include "transform.h"

// Функция для копирования строки из исходного изображения в столбец повернутого изображения
void copy_row_to_column(const struct image *source, struct image *rotated, uint64_t row) {
    // Получаем указатель на начало строки в исходном изображении
    const struct pixel *source_row_ptr = image_pixel(source, 0, row);
    struct pixel *rotated_pixel_ptr = image_pixel(rotated, row, rotated->height - 1);

    for (uint64_t x = 0; x < source->width; x++) {
        // Копируем данные пикселя
        *rotated_pixel_ptr = *source_row_ptr;

        // Переходим к следующему пикселю в исходной строке
        source_row_ptr++;

        // Переходим к следующему пикселю в столбце повернутого изображения (сдвигаемся вверх)
        rotated_pixel_ptr -= rotated->width;
    }
}

struct image rotate_image_90(const struct image *source) {
    // Проверяем, что указатель на исходное изображение не NULL
    if (source == NULL || source->data == NULL) {
        struct image empty = {0};
        return empty;
    }

    // Создаем новое изображение с шириной и высотой, поменянными местами
    struct image rotated = create_image(source->height, source->width);

    // Проверка успешного выделения памяти
    if (rotated.data == NULL) {
        return rotated;
    }

    // Копирование данных с поворотом на 90 градусов
    for (uint64_t y = 0; y < source->height; y++) {
        copy_row_to_column(source, &rotated, y);
    }

    return rotated;
}
