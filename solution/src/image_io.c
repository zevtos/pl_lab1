#include "image_io.h"
#include "bmp.h"
#include <stdio.h>

/**
 * @brief Читает изображение из BMP файла.
 *
 * Открывает файл по указанному пути в режиме "rb" (чтение в двоичном режиме).
 * Затем читает данные изображения в структуру `image` с использованием функции `bmp_from_file`.
 * В случае ошибки выводит сообщение об ошибке и возвращает ненулевой код.
 *
 * @param source_path Путь к BMP файлу для чтения изображения.
 * @param img Указатель на структуру `image`, в которую будут записаны данные изображения.
 * @return 0, если чтение прошло успешно, или 1 в случае ошибки.
 */
int read_image(const char *source_path, struct image *img) {
    FILE *input = fopen(source_path, "rb");
    if (!input) {
        perror("Не удалось открыть исходный файл");
        return 1;
    }

    enum read_status r_status = bmp_from_file(input, img);
    fclose(input);

    if (r_status != READ_OK) {
        fprintf(stderr, "Ошибка при чтении BMP изображения\n");
        return 1;
    }

    return 0;
}

/**
 * @brief Записывает изображение в BMP файл.
 *
 * Открывает файл по указанному пути в режиме "wb" (запись в двоичном режиме).
 * Затем записывает данные изображения из структуры `image` в файл с использованием функции `bmp_to_file`.
 * В случае ошибки выводит сообщение об ошибке и возвращает ненулевой код.
 *
 * @param dest_path Путь к BMP файлу для записи изображения.
 * @param img Указатель на структуру `image`, данные которой необходимо записать в файл.
 * @return 0, если запись прошла успешно, или 1 в случае ошибки.
 */
int write_image(const char *dest_path, const struct image *img) {
    FILE *output = fopen(dest_path, "wb");
    if (!output) {
        perror("Не удалось открыть выходной файл");
        return 1;
    }

    enum write_status w_status = bmp_to_file(output, img);
    fclose(output);

    if (w_status != WRITE_OK) {
        fprintf(stderr, "Ошибка при записи BMP изображения: ");
        switch (w_status) {
            case WRITE_FILE_POINTER_NULL:
                fprintf(stderr, "Указатель на файл NULL\n");
                break;
            case WRITE_IMAGE_POINTER_NULL:
                fprintf(stderr, "Указатель на изображение NULL\n");
                break;
            case WRITE_IMAGE_TOO_LARGE:
                fprintf(stderr, "Размеры изображения слишком большие\n");
                break;
            case WRITE_HEADER_ERROR:
                fprintf(stderr, "Ошибка при записи заголовка BMP\n");
                break;
            case WRITE_ROW_ERROR:
                fprintf(stderr, "Ошибка при записи строки изображения\n");
                break;
            default:
                fprintf(stderr, "Неизвестная ошибка\n");
                break;
        }
        remove(dest_path); // Удаление файла в случае ошибки
        return 1;
    }

    return 0;
}
