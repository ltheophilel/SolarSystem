#ifndef MAIN_H
#define MAIN_H
#include <SDL2/SDL.h>

/**
 * @brief 
 * 
 */
typedef struct Astre Astre;
struct Astre {
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
};

/**
 * @brief 
 * 
 */
typedef struct Point Point;
struct Point {
    int x;
    int y;
};

void version_decision(int argc, char* argv[]);

#endif