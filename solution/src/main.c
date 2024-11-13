#include <stdio.h>
#include "image_io.h"
#include "transform.h"

/**
 * @brief Главная функция программы для поворота изображения на 90 градусов против часовой стрелки.
 *
 * Программа принимает на вход два аргумента: путь к исходному изображению и путь для сохранения трансформированного изображения.
 * Выполняет чтение изображения, его поворот, а затем сохраняет результат в указанный файл.
 *
 * @param argc Количество аргументов командной строки.
 * @param argv Массив строк с аргументами командной строки.
 *             - argv[1] - путь к исходному изображению.
 *             - argv[2] - путь к выходному изображению.
 * @return Код завершения программы: 0 - успешное выполнение, 1 - ошибка.
 */
int main(int argc, char *argv[]) {
    // Проверка количества аргументов командной строки
    if (argc != 3) {
        fprintf(stderr, "Использование: %s <source-image> <transformed-image>\n", argv[0]);
        return 1;
    }

    // Чтение исходного изображения
    struct image img = {0};
    if (read_image(argv[1], &img) != 0) {
        fprintf(stderr, "Ошибка: Не удалось прочитать исходное изображение из '%s'\n", argv[1]);
        return 1;
    }

    // Поворот изображения на 90 градусов против часовой стрелки
    struct image rotated_img = rotate_image_90_counterclockwise(&img);
    destroy_image(&img); // Очистка оригинального изображения после его трансформации

    // Проверка успешности поворота
    if (rotated_img.data == NULL) {
        fprintf(stderr, "Ошибка: Не удалось повернуть изображение\n");
        return 1;
    }

    // Запись повёрнутого изображения в выходной файл
    if (write_image(argv[2], &rotated_img) != 0) {
        fprintf(stderr, "Ошибка: Не удалось записать изображение в '%s'\n", argv[2]);
        destroy_image(&rotated_img); // Очистка памяти, если запись не удалась
        return 1;
    }

    // Очистка памяти для повёрнутого изображения
    destroy_image(&rotated_img);
    return 0;
}