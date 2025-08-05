#ifndef MAIN_H
#define MAIN_H

#include <SDL2/SDL.h>



typedef struct Astre Astre;
struct Astre {
    SDL_Texture *astre;
    int radius;
    Uint8 red;
    Uint8 green;
    Uint8 blue;
    int x;
    int y;
    float vx;
    float vy;
    double angle;
};


#endif