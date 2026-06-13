#ifndef SHAPE_H
#define SHAPE_H
#include <stdbool.h>

#include "compute.h"

SDL_Texture* create_disk(
    SDL_Renderer *renderer,
    int radius,
    Uint8 red,
    Uint8 green,
    Uint8 blue,
    int i,
    int planet_x,
    int planet_y);

#endif
