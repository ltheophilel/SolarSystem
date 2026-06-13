#ifndef MAIN_H
#define MAIN_H

#include <SDL2/SDL.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

typedef struct Astre {
    SDL_Texture *astre;
    int radius;
    Uint8 red;
    Uint8 green;
    Uint8 blue;
    double x;
    double y;
    double vx;
    double vy;
    double angle;
    double mass;
} Astre;

typedef struct Point {
    int x;
    int y;
} Point;

void version_decision(int argc, char* argv[]);

#endif
