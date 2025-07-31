#ifndef DISPLAY_H
#define DISPLAY_H

int sdl_init();

int create_window(SDL_Window **window,const char *title, Uint32 flags);

void create_rectangle(SDL_Surface *screen, SDL_Surface **shape,
                    int width, int height);

void place_centered(SDL_Window *window, SDL_Surface *screen, 
                SDL_Surface *shape, int width, int height);


#endif