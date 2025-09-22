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
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "constants.h"
#include "compute.h"
#include "display.h"
#include "main.h"


static int dynamics = 0;

int main(int argc, char* argv[])
{
    /* Initialisation */
    if (argc > 1) version_decision(argc, argv);
    sdl_init();
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    const char title[] = "Universe";
    create_window(&window, title, &renderer);

    /* Parameters */
    Astre Astres[NB_ASTRES];
    Uint8 colourArray[NB_ASTRES][3] = {{255, 255, 255}, 
    {200, 200, 200}, {220, 230, 160}, {127, 127, 255}, {255, 127, 127},
    {255, 255, 220}, {255, 255, 127}, {127, 255, 210}, {50, 50, 255}};
    SDL_Texture* trajTexture;
    SDL_Surface *textSurface;
    SDL_Texture *textTexture;

    double initial_angles[NB_ASTRES];

    /* Creation */
    init_trajectories(renderer, &trajTexture);
    construct_astres(renderer, Astres, radiusArray, distArray, colourArray, initial_angles);
    initial_speed(Astres);

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

    TTF_Font *font = TTF_OpenFont("fonts/Anta-Regular.ttf", 70);
    if (!font) {
        printf("Error loading the police : %s\n", TTF_GetError());
        return 1;
    }

    /* Main Loop */
    bool hold = true;
    bool pause = false;

    int delay_milliseconds = 0;
    clock_t t;
    double time_taken;
    long int nb_frames = 0;

    int year, month, day;
    get_date(&year, &month, &day);
    int init_year = year;
    int current_year = year;
    while (hold)
    {
        hold = check_event();
        const Uint8 *state = SDL_GetKeyboardState(NULL);
        pause = state[SDL_SCANCODE_SPACE];

        if (pause) {
            goto END_LOOP;
        }
        t = clock();
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        update_pos(Astres, distArray);
        current_year = init_year + compute_year(Astres[3]);
        char year_print[10];
        sprintf(year_print, "%d", current_year);

        // Créer une surface de texte
        SDL_Color textColor = {255, 255, 255, 255};
        textSurface = TTF_RenderText_Solid(font, year_print, textColor);
        if (!textSurface) {
            printf("Error while rendering text : %s\n", TTF_GetError());
            return 1;
        }
        textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        if (!textTexture) {
            printf("Erreur de création de la texture : %s\n", SDL_GetError());
            return 1;
        }
        SDL_Rect textRect = {10, 10, textSurface->w, textSurface->h}; // Position et taille
        SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

        update_trajectory(renderer, trajTexture, Astres);
        SDL_RenderCopy(renderer, trajTexture, NULL, NULL);

        place(renderer, Astres, initial_angles);
        SDL_RenderPresent(renderer);

        t -= clock();
        nb_frames++;
        time_taken += ((double)-t)/CLOCKS_PER_SEC*1000;

        END_LOOP: // use goto for pause
        SDL_Delay(delay_milliseconds);
    }
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
    TTF_CloseFont(font);
    quit_universe(window,renderer, Astres, trajTexture);
    time_taken = time_taken/nb_frames;
    // printf("compute average time = %lf ms\n", time_taken);
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
