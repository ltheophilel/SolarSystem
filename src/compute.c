// COMPUTE
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

#include "constants.h"
#include "compute.h"
#include "main.h"

bool is_in_disk(int x, int y, int radius) {
    int dist_x = x-radius;
    int dist_y = y-radius;
    return ((dist_x)*(dist_x) + (dist_y)*(dist_y) <= radius*radius);
}


void create_disk(SDL_Surface *surface,
                int radius, Uint8 red, Uint8 green, Uint8 blue) 
{
    if (SDL_MUSTLOCK(surface)) SDL_LockSurface(surface);
    Uint32 white = SDL_MapRGB(surface->format, red, green, blue);
    Uint8 *pixels = (Uint8 *)surface->pixels;
    int pitch = surface->pitch;
    const int min_x = 0;
    const int max_x = 2*radius;

    const int min_y = 0;
    const int max_y = 2*radius;

    for (int x = min_x ; x < max_x; x++) {
        for (int y = min_y ; y < max_y ; y++) {
            if (is_in_disk(x,y,radius)) {
               if (x >= 0 && x < surface->w && y >= 0 && y < surface->h) { // ? out Of Bounds double check, to be moved to is in disk.
                   Uint32 *pixelPtr = (Uint32 *)(pixels + y * pitch + x * surface->format->BytesPerPixel);
                   *pixelPtr = white;
                }
            }
        }
    }
    if (SDL_MUSTLOCK(surface)) SDL_UnlockSurface(surface);
}
