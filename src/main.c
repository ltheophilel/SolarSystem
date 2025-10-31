/**
 * @file main.c
 * @author Theophile (ltheophilel on GitHub)
 * @brief main simulation file
 * @version 0.4
 * @date 2025-10-25
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
#include "date.h"
#include "shape.h"


static int dynamics = 0;
static int on_scale = 0;

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
    SDL_Surface *fpsSurface;
    SDL_Texture *fpsTexture;
    const int *distArray, *radiusArray;
    double reduction_factor;

    if (on_scale == 0)
    {
        reduction_factor = reduction_arbitrary;
        distArray = distArray_arbitrary;
        radiusArray = radiusArray_arbitrary;
    }
    else
    {
        reduction_factor = reduction_onscale;
        distArray = distArray_onscale;
        radiusArray = radiusArray_onscale;
    }

    double initial_angles[NB_ASTRES];

    /* Creation */
    init_trajectories(renderer, &trajTexture);
    construct_astres(renderer, Astres, radiusArray, distArray, colourArray, initial_angles);

    /* Version Detection */
    void (*update_pos)(Astre *Astres, const int *distArray, double reduction_factor);
    switch (dynamics)
    {
        case 0:
        update_pos = update_positions_kinematics;
        initial_speed_kinematics(Astres, distArray);
        break;

        case 1:
        initial_speed_dynamics(Astres, distArray,
             reduction_factor, on_scale);
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
    int test = 1;
    bool pause = false;

    int delay_milliseconds = 0;
    clock_t start;
    clock_t end;
    double time_taken = 0;
    double time_checkpoint = 0;
    long int nb_frames = 0;
    long int nb_frames_checkpoint = 0;
    double fps = 0;

    int year, month, day;
    get_date(&year, &month, &day);
    int current_year = year;
    int diff_year = 0;
    int new_year = 0;

    while (hold==1)
    {
        test = check_event();
        user_input_processing(test, &hold, &delay_milliseconds);
        const Uint8 *state = SDL_GetKeyboardState(NULL);
        pause = state[SDL_SCANCODE_SPACE];

        if (pause || delay_milliseconds < 0)
            goto END_LOOP;

        start = clock();
        // Black Screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Positions
        update_pos(Astres, distArray, reduction_factor);

        // Year
        diff_year = compute_year(Astres[3], &new_year);
        current_year += diff_year;
        char year_print[10];
        sprintf(year_print, "%d", current_year);
        // Year Text
        int test_text;
        if (1==diff_year || 0==nb_frames)
        {
            test_text = place_text(renderer, &textSurface, &textTexture, font, year_print);
            if (test_text !=0) return test_text;
        }
        SDL_Rect textRect = {10, 10, textSurface->w, textSurface->h}; // Position and size
        SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

        // FPS
        char fps_array[FPS_PRECISION];
        translate_fps_to_text(fps, fps_array);
        // FPS Text
        test_text = place_text(renderer, &fpsSurface, &fpsTexture, font, fps_array);
        if (test_text !=0) return test_text;
        SDL_Rect fpsRect = {WINDOW_WIDTH-fpsSurface->w-10, 10, fpsSurface->w, fpsSurface->h}; // Position and size
        SDL_RenderCopy(renderer, fpsTexture, NULL, &fpsRect);

        // Trajectories
        update_trajectory(renderer, trajTexture, Astres);
        SDL_RenderCopy(renderer, trajTexture, NULL, NULL);

        // Rendering
        place(renderer, Astres, initial_angles);
        SDL_RenderPresent(renderer);
        end = clock();

        nb_frames++;
        time_taken += ((double)(end-start))*1000/(CLOCKS_PER_SEC);
        if (0==nb_frames%40|| 1==nb_frames)
        {
            fps = 1000*(nb_frames-nb_frames_checkpoint)/(time_taken-time_checkpoint);
            time_checkpoint = time_taken;
            nb_frames_checkpoint = nb_frames;
        }

        END_LOOP: // using goto for pause
        SDL_Delay(delay_milliseconds);
    }
    SDL_FreeSurface(textSurface); // TODO put in quit_universe
    SDL_DestroyTexture(textTexture);
    SDL_FreeSurface(fpsSurface);
    SDL_DestroyTexture(fpsTexture);
    TTF_CloseFont(font);
    quit_universe(window,renderer, Astres, trajTexture);
    // double average_time_taken = time_taken/nb_frames;
    // printf("compute average time = %lf ms\n", average_time_taken);
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
        else if (strcmp(argv[i], "on_scale")==0) {
            on_scale = 1;
        }
    }
}
