/**
 * @file display.c
 * @author Theophile (ltheophilel on GitHub)
 * @brief functions related to SDL
 * @version 0.3
 * @date 2025-08-27
 *
 * @copyright Copyright (c) 2025
 *
 */
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <math.h>

#include "constants.h"
#include "compute.h"
#include "display.h"
#include "main.h"


/**
 * @brief SDL init and error catching
 *
 * @return int
 */
int sdl_init()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
    {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }
    if (TTF_Init() != 0)
    {
        printf("TTF_Init Error: %s\n", TTF_GetError());
        return 1;
    }
    return 0;
}

/**
 * @brief Create a window object
 *
 * @param window
 * @param title
 * @param renderer
 * @return int
 */
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

/**
 * @brief Creates and initialises the astres
 * 
 * @param renderer
 * @param Astres array of the astres
 * @param radiusArray
 * @param distArray
 * @param colourArray
 */
void construct_astres(SDL_Renderer *renderer, Astre *Astres, const int *radiusArray,
        const int *distArray, Uint8 colourArray[][3], double initial_angles[NB_ASTRES])
{
    double today_angles[NB_ASTRES];
    get_today_angles(today_angles);

    for (int i = 0 ; i < NB_ASTRES ; i++) {
        Astre *a = &Astres[i];
        a->radius = radiusArray[i];

        a->red = colourArray[i][0];
        a->green = colourArray[i][1];
        a->blue = colourArray[i][2];
        a->angle = today_angles[i];

        initial_angles[i] = a->angle;
        a->x = distArray[i]*cos(a->angle) + WINDOW_WIDTH/2;
        a->y = -distArray[i]*sin(a->angle) + WINDOW_HEIGHT/2;

        a->mass = massArray[i];
        a->astre = create_disk(renderer, a->radius, a->red, a->green, a->blue, i, a->x-WINDOW_WIDTH/2, a->y-WINDOW_HEIGHT/2);
    }
}

/**
 * @brief Initialises the trajectories
 *
 * @param renderer
 * @param trajTex Texture for trajectories
 */
void init_trajectories(SDL_Renderer* renderer,
                       SDL_Texture** trajTex)
{
    *trajTex = SDL_CreateTexture(renderer,
        SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
        WINDOW_WIDTH, WINDOW_HEIGHT);
    SDL_SetTextureBlendMode(*trajTex, SDL_BLENDMODE_BLEND);

    SDL_SetRenderTarget(renderer, *trajTex);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    SDL_SetRenderTarget(renderer, NULL);
}

/**
 * @brief Updates tre traj Texture with the new
 * astre positions
 *
 * @param renderer
 * @param trajTex
 * @param x coordinate
 * @param y coordinate
 */
void update_trajectory(SDL_Renderer* renderer,
                       SDL_Texture* trajTex,
                       Astre Astres[NB_ASTRES])
{
    SDL_SetRenderTarget(renderer, trajTex);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    for (int i = 1; i < NB_ASTRES; i++) 
    {
        int x = (int)Astres[i].x;
        int y = (int)Astres[i].y;
        if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT) {
            SDL_RenderDrawPoint(renderer, x, y);
        }
    }
    SDL_SetRenderTarget(renderer, NULL);
}

/**
 * @brief Place the textures on the screen
 *
 * @param renderer 
 * @param Astres 
 */
void place(SDL_Renderer *renderer, Astre *Astres, double initial_angles[NB_ASTRES])
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
        double rotation_angle = -(a->angle-initial_angles[i])*180/PI;

        SDL_RenderCopyEx(renderer, a->astre, NULL, &position, rotation_angle, NULL, 0);
    }
}

/**
 * @brief Destroy and Quit SDL
 *
 * @param window
 * @param renderer
 * @param Astres
 * @param trajTextures
 */
void quit_universe(SDL_Window *window, SDL_Renderer *renderer,
                   Astre *Astres, SDL_Texture *trajTexture)
{
    for (int i = 0 ; i < NB_ASTRES ; i++) {
        SDL_DestroyTexture((Astres+i)->astre);
    }
    SDL_DestroyTexture(trajTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}

/**
 * @brief Detect when the escape key is pressed down
 *
 * @param event
 * @return true
 * @return false
 */
bool escape_key(SDL_Event event)
{
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

/**
 * @brief Detect quitting from user
 *
 * @return true
 * @return false
 */
bool check_event()
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch(event.type)
        {
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
