#include <stdio.h>
#include "image_io.h"
#include "transform.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Использование: %s <source-image> <transformed-image>\n", argv[0]);
        return 1;
    }

    struct image img = {0};
    if (read_image(argv[1], &img) != 0) {
        return 1;
    }

    struct image rotated_img = rotate_image(&img);
    destroy_image(&img);

    if (write_image(argv[2], &rotated_img) != 0) {
        destroy_image(&rotated_img);
        return 1;
    }

    destroy_image(&rotated_img);
    return 0;
}
