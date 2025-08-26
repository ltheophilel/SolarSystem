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
    SDL_WINDOWPOS_CENTERED,WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN, SDL_WINDOW_FULLSCREEN);

    if (*window == NULL) {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        return 1;
    }
    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    return 0;
}


void construct_astres(SDL_Renderer *renderer, Astre *Astres, const int *radiusArray,
        const int *distArray, Uint8 colourArray[][3])
{
    srand(11871214);
    for (int i = 0 ; i < NB_ASTRES ; i++) {
        Astre *a = &Astres[i];
        a->radius = radiusArray[i];

        a->red = colourArray[i][0];
        a->green = colourArray[i][1];
        a->blue = colourArray[i][2];

        a->angle = (rand() % 360)*PI/180;
        a->x = distArray[i]*cos(a->angle) + WINDOW_WIDTH/2;
        a->y = -distArray[i]*sin(a->angle) + WINDOW_HEIGHT/2;

        a->mass = massArray[i];
        a->astre = create_disk(renderer, a->radius, a->red, a->green, a->blue);
    }
}

void init_trajectories(SDL_Renderer* renderer,
                       SDL_Texture* trajTex[NB_ASTRES])
{
    for (int i = 0; i < NB_ASTRES; i++) {
        trajTex[i] = SDL_CreateTexture(renderer,
                                            SDL_PIXELFORMAT_RGBA8888,
                                            SDL_TEXTUREACCESS_TARGET,
                                            WINDOW_WIDTH,
                                            WINDOW_HEIGHT);
        SDL_SetTextureBlendMode(trajTex[i], SDL_BLENDMODE_BLEND);

        SDL_SetRenderTarget(renderer, trajTex[i]);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);
    }
    SDL_SetRenderTarget(renderer, NULL);
}


void update_trajectory(SDL_Renderer* renderer,
                       SDL_Texture* trajTex,
                       int x, int y)
{
    if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT) {
        SDL_SetRenderTarget(renderer, trajTex);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawPoint(renderer, x, y);

        SDL_SetRenderTarget(renderer, NULL);
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
        position.x = (int)(a->x - a->radius);
        position.y = (int)(a->y - a->radius);
        position.w = 2 * a->radius;
        position.h = 2 * a->radius;

        SDL_RenderCopy(renderer, a->astre, NULL, &position);
    }
}


void quit_universe(SDL_Window *window, SDL_Renderer *renderer, Astre *Astres, SDL_Texture *trajTextures[NB_ASTRES]) {
    for (int i = 0 ; i < NB_ASTRES ; i++) {
        SDL_DestroyTexture((Astres+i)->astre);
        SDL_DestroyTexture(trajTextures[i]);
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
