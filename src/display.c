// DISPLAY
#include <SDL2/SDL.h>
#include <math.h>

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


int create_window(SDL_Window **window, const char *title, SDL_Renderer **renderer)
{
    *window = SDL_CreateWindow(title,
    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
    WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

    if (*window == NULL) {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        return 1;
    }
    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    return 0;
}


void construct_astres(SDL_Renderer *renderer, Astre *Astres, const int *radiusArray,
        const int *distArray, Uint8 colourArray[][3], float speedArray[][2])
{
    for (int i = 0 ; i < NB_ASTRES ; i++) {
        Astre *a = &Astres[i];
        a->radius = radiusArray[i];
        a->x = WINDOW_WIDTH/2 + distArray[i];
        a->y = WINDOW_HEIGHT/2;

        a->red = colourArray[i][0];
        a->green = colourArray[i][1];
        a->blue = colourArray[i][2];

        a->vx = speedArray[i][0];
        a->vy = speedArray[i][1];
        a->angle = 0;

        a->astre = create_disk(renderer, a->radius, a->red, a->green, a->blue);
    }
}


void place(SDL_Renderer *renderer, Astre *Astres)
{
    for (int i = 0; i < NB_ASTRES ; i++) {
        Astre *a = &Astres[i];

        if (!a->astre) {
            SDL_Log("Astre %d : texture NULL during placement !", i);
            continue;
        }

        SDL_Rect position;
        position.x = a->x - a->radius;
        position.y = a->y - a->radius;
        position.w = 2 * a->radius;
        position.h = 2 * a->radius;

        SDL_RenderCopy(renderer, a->astre, NULL, &position);
    }
}


void quit_universe(SDL_Window *window, SDL_Renderer *renderer, Astre *Astres) {
    for (int i = 0 ; i < NB_ASTRES ; i++) {
        SDL_DestroyTexture((Astres+i)->astre);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}


bool escape_key(SDL_Event event) {
    switch (event.key.keysym.sym)
    {
        case SDLK_ESCAPE:
            return false;
            break;
        
        default:
            break;
    }
    return true;
}


bool check_event() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch(event.type) {
            case SDL_QUIT:
                return false;
                break;
            case SDL_KEYDOWN:
                return escape_key(event);
                break;
        }
    }
    return true;
}
