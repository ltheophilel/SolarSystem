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


SDL_Texture* create_disk(SDL_Renderer *renderer,
                         int radius,
                         Uint8 red, Uint8 green, Uint8 blue)
{
    int diameter = 2 * radius;
    SDL_Surface *surface = SDL_CreateRGBSurfaceWithFormat(0, diameter, diameter, 32, SDL_PIXELFORMAT_RGBA8888);

    SDL_SetSurfaceBlendMode(surface, SDL_BLENDMODE_NONE);
    if (SDL_MUSTLOCK(surface)) SDL_LockSurface(surface);

    Uint32 color = SDL_MapRGBA(surface->format, red, green, blue, 255);  // opaque
    Uint8 *pixels = (Uint8 *)surface->pixels;
    int pitch = surface->pitch;

    for (int x = 0; x < diameter; ++x) {
        for (int y = 0; y < diameter; ++y) {
            if (is_in_disk(x, y, radius)) {
                Uint32 *pixelPtr = (Uint32 *)(pixels + y * pitch + x * 4); // 4 bytes per pixel (RGBA8888)
                *pixelPtr = color;
            }
        }
    }

    if (SDL_MUSTLOCK(surface)) SDL_UnlockSurface(surface);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);

    SDL_FreeSurface(surface);
    return texture;
}


float mean_sqrt(float a, float b) { // Norme 2
    return sqrt(a*a + b*b);
}


void update_positions(Astre *Astres, const int *distArray) {
    for (int i = 1 ; i < NB_ASTRES ; i++) { // Uniform Circular Mouvement
        Astre *a = &Astres[i];
        a->angle = a->angle + mean_sqrt(a->vx, a->vy)/distArray[i];
        a->x = distArray[i]*cos(a->angle) + WINDOW_WIDTH/2;
        a->y = -distArray[i]*sin(a->angle) + WINDOW_HEIGHT/2;
    }
}
