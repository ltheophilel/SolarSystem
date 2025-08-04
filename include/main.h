#ifndef MAIN_H
#define MAIN_H

#include <SDL2/SDL.h>

void pause();

typedef struct Astre Astre;
struct Astre {
    SDL_Surface *astre;
    int radius;
    Uint8 red;
    Uint8 green;
    Uint8 blue;
    int x;
    int y;
};


#endif