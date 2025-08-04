#ifndef COMPUTE_H
#define COMPUTE_H
#include <stdbool.h>

// define coordinates structure
bool is_in_disk(int x, int y, int radius);

void create_disk(SDL_Surface *surface,
                      int radius, Uint8 red, Uint8 green, Uint8 blue);

#endif