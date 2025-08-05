#ifndef COMPUTE_H
#define COMPUTE_H
#include <stdbool.h>

#include "constants.h"
#include "compute.h"
#include "display.h"
#include "main.h"

// define coordinates structure
bool is_in_disk(int x, int y, int radius);

SDL_Texture* create_disk(SDL_Renderer *renderer,
                int radius, Uint8 red, Uint8 green, Uint8 blue);

void update_positions(Astre *Astres, const int *distArray);


#endif