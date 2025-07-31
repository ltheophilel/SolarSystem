// DISPLAY
#include <SDL2/SDL.h>
#include "constants.h"
#include "display.h"

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



void create_rectangle(SDL_Surface *screen, SDL_Surface **shape,
                      int width, int height)
{
    *shape = SDL_CreateRGBSurface(0, width, height,
                                  screen->format->BitsPerPixel,
                                  screen->format->Rmask,
                                  screen->format->Gmask,
                                  screen->format->Bmask,
                                  0);
    if (*shape == NULL) {
        printf("Erreur : %s\n", SDL_GetError());
        return;
    }

    SDL_FillRect(*shape, NULL, SDL_MapRGB(screen->format, 255, 255, 255));
}


void place_centered(SDL_Window *window, SDL_Surface *screen, 
                    SDL_Surface *shape, int width, int height)
{
    if (!screen || !shape) {
        fprintf(stderr, "Erreur : screen ou shape est NULL dans place_centered()\n");
        return;
    }

    SDL_Rect position;
    position.x = WINDOW_WIDTH / 2 - width / 2;
    position.y = WINDOW_HEIGHT / 2 - height / 2;

    if (SDL_BlitSurface(shape, NULL, screen, &position) != 0) {
        fprintf(stderr, "SDL_BlitSurface Error: %s\n", SDL_GetError());
        return;
    }

    if (SDL_UpdateWindowSurface(window) != 0) {
        fprintf(stderr, "SDL_UpdateWindowSurface Error: %s\n", SDL_GetError());
    }
}
