#ifndef DISPLAY_H
#define DISPLAY_H
#include "main.h"

int sdl_init();

int create_window(SDL_Window **window,const char *title, Uint32 flags);


void construct_astres(Astre *Astres, const int *radiusArray,
    const int *distArray, Uint8 colourArray[][3]);
    
void place(SDL_Window *window, SDL_Surface *screen, Astre *Astres);

void quit_universe(SDL_Window *window, Astre *Astres);

#endif