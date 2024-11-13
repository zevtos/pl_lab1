#ifndef BMP_H
#define BMP_H

#include <stdio.h>
#include "image.h"

// Константы для BMP формата
static const uint16_t BMP_SIGNATURE = 0x4D42;  // Сигнатура файла BMP (ASCII код символов 'B' и 'M')
static const uint16_t BMP_BPP = 24;            // Количество бит на пиксель (24 для RGB)

// Статусы чтения BMP файла
enum read_status {
    READ_OK = 0,                // Чтение прошло успешно
    READ_INVALID_SIGNATURE,     // Неверная сигнатура BMP файла
    READ_INVALID_BITS,          // Неподдерживаемое количество бит на пиксель
    READ_INVALID_HEADER,        // Неверный заголовок BMP
    READ_IO_ERROR,              // Ошибка ввода-вывода при чтении файла
    READ_MEMORY_ERROR           // Ошибка выделения памяти
};

// Статусы записи BMP файла
enum write_status {
    WRITE_OK = 0,               // Запись прошла успешно
    WRITE_ERROR                 // Ошибка при записи BMP файла
};

// Прототипы функций для чтения и записи BMP файлов
enum read_status from_bmp(FILE *in, struct image *img);

enum write_status to_bmp(FILE *out, const struct image *img);

#pragma pack(push, 1)
// Структура для заголовка BMP файла, соответствующая спецификации BMP
struct bmp_header {
    uint16_t bfType;              // Сигнатура файла BMP, всегда равна 0x4D42
    uint32_t bfileSize;           // Общий размер файла в байтах
    uint32_t bfReserved;          // Зарезервированное поле, должно быть 0
    uint32_t bOffBits;            // Смещение начала данных изображения относительно начала файла
    uint32_t biSize;              // Размер структуры BITMAPINFOHEADER
    int32_t biWidth;              // Ширина изображения в пикселях
    int32_t biHeight;             // Высота изображения в пикселях
    uint16_t biPlanes;            // Количество цветовых плоскостей, всегда 1
    uint16_t biBitCount;          // Количество бит на пиксель (24 для RGB)
    uint32_t biCompression;       // Тип сжатия (0 означает отсутствие сжатия)
    uint32_t biSizeImage;         // Размер изображения в байтах
    int32_t biXPelsPerMeter;      // Горизонтальное разрешение в пикселях на метр
    int32_t biYPelsPerMeter;      // Вертикальное разрешение в пикселях на метр
    uint32_t biClrUsed;           // Количество используемых цветов в палитре (0 если все)
    uint32_t biClrImportant;      // Количество важных цветов (0 если все важны)
};
#pragma pack(pop)

#endif // BMP_H
