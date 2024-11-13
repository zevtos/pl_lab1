#ifndef BMP_H
#define BMP_H

#include <stdio.h>
#include "image.h"

// Константы для BMP формата
static const uint16_t BMP_SIGNATURE = 0x4D42;  // Сигнатура файла BMP (BM)
static const uint16_t BMP_BPP = 24;            // Количество бит на пиксель (24 для RGB)
static const uint32_t BITMAPINFOHEADER_SIZE = 40;
#define BMP_PADDING 4                          // BMP строки должны быть кратны 4 байтам

// Статусы чтения BMP файла
enum read_status {
    /**
     * Чтение прошло успешно
     */
    READ_OK = 0,

    /**
     * Неверная сигнатура BMP файла (сигнатура отличается от 0x4D42)
     */
    READ_INVALID_SIGNATURE,

    /**
     * Файл содержит неподдерживаемый формат количества битов на пиксель (должно быть 24 bpp)
     */
    READ_INVALID_BITS,

    /**
     * Ошибка при чтении заголовка BMP файла (несоответствие размера или структуры)
     */
    READ_INVALID_HEADER,

    /**
     * Ошибка ввода-вывода при чтении файла
     */
    READ_IO_ERROR,

    /**
     * Ошибка выделения памяти при загрузке изображения
     */
    READ_MEMORY_ERROR
};

// Статусы записи BMP файла
enum write_status {
    /**
     * Запись прошла успешно
     */
    WRITE_OK = 0,

    /**
     * Ошибка: указатель на файл NULL
     */
    WRITE_FILE_POINTER_NULL,

    /**
     * Ошибка: указатель на изображение NULL
     */
    WRITE_IMAGE_POINTER_NULL,

    /**
     * Ошибка: размеры изображения слишком большие
     */
    WRITE_IMAGE_TOO_LARGE,

    /**
     * Ошибка при записи заголовка BMP
     */
    WRITE_HEADER_ERROR,

    /**
     * Ошибка при записи строки изображения
     */
    WRITE_ROW_ERROR
};
// Прототипы функций для чтения и записи BMP файлов
/**
 * @brief Читает изображение из BMP файла и загружает его в структуру `image`.
 *
 * @param in Указатель на файл BMP для чтения.
 * @param img Указатель на структуру `image` для хранения изображения.
 * @return Статус чтения, указывающий на успешность операции или тип ошибки.
 */
enum read_status bmp_from_file(FILE *in, struct image *img);

/**
 * @brief Записывает изображение из структуры `image` в BMP файл.
 *
 * @param out Указатель на файл BMP для записи.
 * @param img Указатель на структуру `image` для записи.
 * @return Статус записи, указывающий на успешность операции или тип ошибки.
 */
enum write_status bmp_to_file(FILE *out, const struct image *img);

#pragma pack(push, 1)
// Структура для заголовка BMP файла, соответствующая спецификации BMP
struct bmp_header {
    uint16_t bfType;              // Сигнатура файла BMP, всегда равна 0x4D42
    uint32_t bfileSize;           // Общий размер файла в байтах
    uint32_t bfReserved;          // Зарезервированное поле, должно быть 0
    uint32_t bOffBits;            // Смещение начала данных изображения относительно начала файла
    uint32_t biSize;              // Размер структуры BITMAPINFOHEADER
    uint32_t biWidth;              // Ширина изображения в пикселях
    uint32_t biHeight;             // Высота изображения в пикселях
    uint16_t biPlanes;            // Количество цветовых плоскостей, всегда 1
    uint16_t biBitCount;          // Количество бит на пиксель (24 для RGB)
    uint32_t biCompression;       // Тип сжатия (0 означает отсутствие сжатия)
    uint32_t biSizeImage;         // Размер изображения в байтах
    uint32_t biXPelsPerMeter;      // Горизонтальное разрешение в пикселях на метр
    uint32_t biYPelsPerMeter;      // Вертикальное разрешение в пикселях на метр
    uint32_t biClrUsed;           // Количество используемых цветов в палитре (0 если все)
    uint32_t biClrImportant;      // Количество важных цветов (0 если все важны)
};
#pragma pack(pop)

#endif // BMP_H
