#ifndef DISPLAY_H
#define DISPLAY_H
#include "main.h"

int sdl_init();

bool escape_key(SDL_Event event);

bool check_event();

int create_window(SDL_Window **window,const char *title, SDL_Renderer **renderer);

void construct_astres(SDL_Renderer *renderer, Astre *Astres, const int *radiusArray,
    const int *distArray, Uint8 colourArray[][3]);

void init_trajectories(SDL_Renderer* renderer,
                       SDL_Texture* trajTex[NB_ASTRES]);

void update_trajectory(SDL_Renderer* renderer,
                       SDL_Texture* trajTex,
                       int x, int y);

void place(SDL_Renderer *renderer, Astre *Astres);

void quit_universe(SDL_Window *window, SDL_Renderer *renderer, Astre *Astres, SDL_Texture *trajTextures[NB_ASTRES]);

#endif