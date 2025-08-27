/**
 * @file main.c
 * @author Theophile (ltheophilel on GitHub)
 * @brief main simulation file
 * @version 0.3
 * @date 2025-08-26
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

#include "constants.h"
#include "compute.h"
#include "display.h"
#include "main.h"


static int dynamics = 0;

int main(int argc, char* argv[])
{
    if (argc > 1) version_decision(argc, argv);
    sdl_init();
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    const char title[] = "Universe";
    create_window(&window, title, &renderer);

    /* Initialisation */

    Astre Astres[NB_ASTRES];
    Uint8 colourArray[NB_ASTRES][3] = {{255, 255, 255}, 
    {200, 200, 200}, {220, 230, 160}, {127, 127, 255}, {255, 127, 127},
    {255, 255, 220}, {255, 255, 127}, {127, 255, 210}, {50, 50, 255}};
    SDL_Texture* trajTextures[NB_ASTRES];
    double initial_angles[NB_ASTRES];

    init_trajectories(renderer, trajTextures);
    construct_astres(renderer, Astres, radiusArray, distArray, colourArray, initial_angles);
    second_law_kepler(Astres);

        /* Version Detection */
        void (*update_pos)(Astre *Astres, const int *distArray);
        switch (dynamics)
        {
        case 0:
            update_pos = update_positions;
            break;

        case 1:
            update_pos = update_positions_dynamics;
            break;

        default:
            break;
        }

    /* Main Loop */
    bool hold = true;
    int delay_milliseconds = 17;
    while (hold) {
        hold = check_event();
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        update_pos(Astres, distArray);

        for (int i = 1; i < NB_ASTRES; i++) {
            int x = (int)Astres[i].x;
            int y = (int)Astres[i].y;
            update_trajectory(renderer, trajTextures[i], x, y);
            SDL_RenderCopy(renderer, trajTextures[i], NULL, NULL);
        }
        place(renderer, Astres, initial_angles);
        /* for (int i = 0; i < NB_ASTRES; i++) 
        { // DEBUG
            printf("Astre %d: x = %f, y = %f\n", i, Astres[i].x, Astres[i].y);
        } */

        SDL_RenderPresent(renderer);
        SDL_Delay(delay_milliseconds);
    }
    quit_universe(window,renderer, Astres, trajTextures);
    return 0;
}

/**
 * @brief Detect version input information
 * 
 * @param argc 
 * @param argv 
 */
void version_decision(int argc, char* argv[])
{
    for (int i = 1; i < argc ; i++)
    {
        if (strcmp(argv[i], "dynamics")==0) {
            dynamics = 1;
        }
    }
}