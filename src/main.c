#include <raylib.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_VIRTUAL_PIXELS 15
#define BUFFER 256

const Vector2 origin = {35, 35};
const Vector2 sides = {70, 70};

typedef struct {
    Color color;
    bool pixels[MAX_VIRTUAL_PIXELS];
} identicon_s;

// TODO: Don't generete white
identicon_s new_identicon() {
    identicon_s new;
    for (uint8_t i = 0; i < MAX_VIRTUAL_PIXELS; i++) {
        new.pixels[i] = (bool)(rand() % 2);
    }
    new.color = (Color){(rand() % 256), (rand() % 256), (rand() % 256)};
    return new;
}

void print_help() {
    printf("-h:                    see the command istructions\n");
    printf("-r <file name>:        to make a random image identicon\n");
    printf("-s <seed> <file name>: to make a random image identicon with a "
           "specific seed\n");
}

void debug_print(const identicon_s* identicon, const time_t* seed) {
    printf("Seed: %ld\n", *seed);
    printf("Color: r(%d), g(%d), b(%d)\n", identicon->color.r,
           identicon->color.g, identicon->color.b);
    for (uint8_t i = 0; i < MAX_VIRTUAL_PIXELS; i++) {
        printf("%c", (identicon->pixels[i] + 35));
        if (i % 5 == 4) {
            printf("\n");
        }
    }
}

void try_set_name(char* name, char* string) {
    if (strlen(string) >= BUFFER) {
        printf("file name is too long!\n");
    } else {
        strcpy(name, string);
    }
}

int main(int argc, char* argv[]) {

    time_t seed = -1;
    char file_name[BUFFER];
    switch (argc) {
        case 2:
            if (strcmp(argv[1], "-h") == 0) {
                print_help();
                return 0;
            }
        case 4:
            if (strcmp(argv[1], "-s") == 0) {
                seed = atoi(argv[2]);
                try_set_name(file_name, argv[3]);
            }
            break;
        case 3:
            if (strcmp(argv[1], "-r") != 0) {
                return 0;
            }
            try_set_name(file_name, argv[2]);
            break;
        default:
            print_help();
            printf("%d", argc);
            return 0;
    }

    if (seed < 0) {
        seed = time(NULL);
    }

    srand(seed);

    identicon_s identicon = new_identicon();

    debug_print(&identicon, &seed);

    Image image = GenImageColor(420, 420, (Color){240, 240, 240});
    for (uint8_t i = 0; i < 5; i++) {
        if (i == 0 || i == 4) {
            for (uint8_t j = 0; j < 5; j++) {
                if (identicon.pixels[j]) {
                    ImageDrawRectangle(&image, origin.x + (sides.x * i),
                                       origin.y + (sides.y * j), sides.x,
                                       sides.y, identicon.color);
                }
            }
        }
        if (i == 1 || i == 3) {
            for (uint8_t j = 0; j < 5; j++) {
                if (identicon.pixels[j + 5]) {
                    ImageDrawRectangle(&image, origin.x + (sides.x * i),
                                       origin.y + (sides.y * j), sides.x,
                                       sides.y, identicon.color);
                }
            }
        }
        if (i == 2) {
            for (uint8_t j = 0; j < 5; j++) {
                if (identicon.pixels[j + 10]) {
                    ImageDrawRectangle(&image, origin.x + (sides.x * i),
                                       origin.y + (sides.y * j), sides.x,
                                       sides.y, identicon.color);
                }
            }
        }
    }
    ExportImage(image, strcat(file_name, ".jpg"));

    return 0;
}
