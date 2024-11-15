#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "image.h"

/**
 * @brief Поворачивает изображение на 90 градусов против часовой стрелки.
 *
 * Создает новое изображение, в котором исходное изображение поворачивается на 90 градусов против часовой стрелки.
 * Выделяется память для нового изображения, и пиксели переносятся с учетом нового положения.
 *
 * @param source Указатель на исходное изображение, которое нужно повернуть.
 * @return Новая структура `image`, содержащая повернутое изображение.
 */
struct image rotate_image_90_counterclockwise(const struct image *source);

#endif // TRANSFORM_H
