#include "transform.h"

/**
 * @brief Копирует строку из исходного изображения в соответствующий столбец повернутого изображения.
 *
 * Эта функция копирует пиксели из заданной строки исходного изображения и размещает их в соответствующем столбце повернутого изображения,
 * реализуя поворот изображения на 90 градусов против часовой стрелки.
 *
 * @param source Указатель на исходное изображение.
 * @param rotated Указатель на изображение, в которое будут скопированы данные.
 * @param row Номер строки в исходном изображении, которую необходимо скопировать.
 */
void copy_row_to_column(const struct image *source, struct image *rotated, uint64_t row) {
    // Получаем указатель на начало строки в исходном изображении
    const struct pixel *source_row_ptr = image_pixel(source, 0, row);
    struct pixel *rotated_pixel_ptr = image_pixel(rotated, row, rotated->height - 1);

    // Копирование пикселей строки в столбец повернутого изображения
    for (uint64_t x = 0; x < source->width; x++) {
        *rotated_pixel_ptr = *source_row_ptr;

        // Переходим к следующему пикселю в исходной строке
        source_row_ptr++;

        // Переходим к следующему пикселю в столбце повернутого изображения (сдвигаемся вверх)
        rotated_pixel_ptr -= rotated->width;
    }
}

/**
 * @brief Поворачивает изображение на 90 градусов против часовой стрелки.
 *
 * Создает новое изображение, в котором ширина и высота исходного изображения меняются местами.
 * Каждый пиксель исходного изображения копируется в новое положение, соответствующее повороту на 90 градусов.
 *
 * @param source Указатель на исходное изображение.
 * @return Новая структура `image`, содержащая повернутое изображение. Если выделение памяти не удалось, структура будет содержать NULL в поле `data`.
 */
struct image rotate_image_90_counterclockwise(const struct image *source) {
    // Проверяем, что указатель на исходное изображение и данные изображения не NULL
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
