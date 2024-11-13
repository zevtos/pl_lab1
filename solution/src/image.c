#include "image.h"
#include <stdlib.h>
#include <limits.h>  // Для проверки переполнения

/**
 * @brief Создает изображение с указанной шириной и высотой.
 *
 * Выделяет память для массива пикселей и инициализирует их нулями. Если ширина или высота равны нулю
 * или происходит переполнение при вычислении размера памяти, возвращает пустую структуру.
 *
 * @param width Ширина изображения в пикселях.
 * @param height Высота изображения в пикселях.
 * @return Структура `image`, содержащая данные нового изображения. Если выделение памяти не удалось, возвращается структура с `data` равной NULL.
 */
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

    // Проверка успешного выделения памяти
    if (!img.data) {
        img.width = 0;
        img.height = 0;
    }

    return img;
}

/**
 * @brief Освобождает память, выделенную под изображение.
 *
 * Освобождает память, выделенную для массива пикселей изображения, и обнуляет поля структуры `image`.
 *
 * @param img Указатель на структуру `image`, которую необходимо уничтожить.
 */
void destroy_image(struct image *img) {
    if (img && img->data) {
        free(img->data);
        img->data = NULL;
        img->width = 0;
        img->height = 0;
    }
}

/**
 * @brief Возвращает указатель на пиксель по заданным координатам.
 *
 * Предоставляет безопасный доступ к пикселю изображения по координатам (x, y).
 * Если координаты выходят за пределы изображения, возвращает `NULL`.
 *
 * @param img Указатель на структуру `image`.
 * @param x Координата X (горизонтальная).
 * @param y Координата Y (вертикальная).
 * @return Указатель на пиксель по заданным координатам или `NULL`, если координаты неверны.
 */
struct pixel *image_pixel(const struct image *img, uint64_t x, uint64_t y) {
    if (x >= img->width || y >= img->height) {
        return NULL; // Вернуть NULL, если координаты вне пределов изображения
    }
    return &img->data[y * img->width + x];
}
