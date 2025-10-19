#ifndef SHAPE_H
#define SHAPE_H
#include <stdbool.h>
#include <SDL2/SDL.h>

#include "constants.h"
#include "compute.h"
#include "display.h"
#include "main.h"

bool is_in_disk(int x, int y, int radius, int i);

bool is_in_shadow(int x, int y, int planet_x, int planet_y, int radius);

SDL_Texture* create_disk(SDL_Renderer *renderer,
                        int radius, Uint8 red, Uint8 green, Uint8 blue, int i, int planet_x, int planet_y);

#endif