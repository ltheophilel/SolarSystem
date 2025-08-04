// DISPLAY
#include <SDL2/SDL.h>

#include "constants.h"
#include "compute.h"
#include "display.h"
#include "main.h"


int sdl_init() 
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
    {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }
    return 0;
}


int create_window(SDL_Window **window, const char *title, Uint32 flags)
{
    *window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                               WINDOW_WIDTH, WINDOW_HEIGHT, flags);
    if (*window == NULL) {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        return 1;
    }
    return 0;
}


void construct_astres(Astre *Astres, const int *radiusArray,
                    const int *distArray, Uint8 colourArray[][3]) {
    for (int i = 0 ; i < NB_ASTRES ; i++) {
        Astre *a = &Astres[i];
        a->radius = radiusArray[i];
        a->astre = SDL_CreateRGBSurface(0, 2*radiusArray[i], 2*radiusArray[i], 32, 0, 0, 0, 0);
        a->x = WINDOW_WIDTH/2 + distArray[i];
        a->y = WINDOW_HEIGHT/2;
        a->red = colourArray[i][0];
        a->green = colourArray[i][1];
        a->blue = colourArray[i][2];
        create_disk(a->astre, a->radius, a->red, a->green, a->blue);
    }
}


void place(SDL_Window *window, SDL_Surface *screen, Astre *Astres)
{
    for (int i = 0; i < NB_ASTRES ; i++) {
        Astre *a = &Astres[i];
        if (!screen || !a->astre) {
            fprintf(stderr, "Error : screen or shape is NULL in place_centered()\n");
            return;
        }
        SDL_Rect position;
        position.x = a->x - a->radius;
        position.y = a->y - a->radius;
        
        if (SDL_BlitSurface(a->astre, NULL, screen, &position) != 0) {
            fprintf(stderr, "SDL_BlitSurface Error: %s\n", SDL_GetError());
            return;
        }
        
        if (SDL_UpdateWindowSurface(window) != 0) {
            fprintf(stderr, "SDL_UpdateWindowSurface Error: %s\n", SDL_GetError());
        }
    }
}


void quit_universe(SDL_Window *window, Astre *Astres) {
    for (int i = 0 ; i < NB_ASTRES ; i++) {
        SDL_FreeSurface((Astres+i)->astre);
    }
    SDL_DestroyWindow(window);
    SDL_Quit();
}
