#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#include "constants.h"
#include "compute.h"
#include "display.h"
#include "main.h"


int main() 
{
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

    construct_astres(renderer, Astres, radiusArray, distArray, colourArray);
    second_law_kepler(Astres);

    /* Main Loop */
    bool hold = true;
    int delay_milliseconds = 17;
    while (hold) { 
        hold = check_event();
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        #ifdef DYNAMICS
        update_positions_dynamics(Astres);
        #else
        update_positions(Astres, distArray);
        #endif

        place(renderer, Astres);
        /* for (int i = 0; i < NB_ASTRES; i++) {
            printf("Astre %d: x = %f, y = %f\n", i, Astres[i].x, Astres[i].y);
            // render Astres[i]
        } */

        SDL_RenderPresent(renderer);
        SDL_Delay(delay_milliseconds); 
    }

    quit_universe(window,renderer, Astres);
    return 0;
}
