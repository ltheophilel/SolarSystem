#ifndef DISPLAY_H
#define DISPLAY_H
#include "main.h"

int sdl_init();

int create_window(SDL_Window **window,const char *title, SDL_Renderer **renderer);

void construct_astres(SDL_Renderer *renderer, Astre *Astres, const int *radiusArray,

const int *distArray, Uint8 colourArray[][3], double initial_angles[NB_ASTRES]);

void init_trajectories(SDL_Renderer* renderer,
SDL_Texture** trajTex);

void update_trajectory(SDL_Renderer* renderer,
    SDL_Texture* trajTex,
    Astre Astres[NB_ASTRES]);

void place(SDL_Renderer *renderer, Astre *Astres, double initial_angles[NB_ASTRES]);

int place_text(SDL_Renderer *renderer, SDL_Surface **textSurface, 
    SDL_Texture **textTexture, TTF_Font* font,
    char year_print[10]);

void translate_fps_to_text(double fps, char fps_array[FPS_PRECISION]);

void quit_universe(SDL_Window *window, SDL_Renderer *renderer, Astre *Astres, SDL_Texture *trajTexture);

int which_key(SDL_Event event);

int check_event();

void user_input_processing(int test, bool *hold, int *delay_milliseconds);


#endif