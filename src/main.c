#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

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
    
    const int radiusArray[NB_ASTRES] = {40, 5, 10, 10, 8, 25, 20, 16, 16};
    Uint8 colourArray[NB_ASTRES][3] = {{255, 255, 255}, 
    {200, 200, 200}, {220, 230, 160}, {127, 127, 255}, {255, 127, 127},
    {255, 255, 220}, {255, 255, 127}, {127, 255, 210}, {50, 50, 255}};
    const int distArray[NB_ASTRES] = {0, DIST_MERCURY, DIST_VENUS, DIST_EARTH, 
        DIST_MARS, DIST_JUPITER, DIST_SATURN, DIST_URANUS, DIST_NEPTUNE};
    float speedArray[NB_ASTRES][2] = {{0,0}, {0,-0.2}, {0,-0.4}, {0,-0.6},
        {0,-1}, {0,-1}, {0,-1}, {0,-1}, {0,-1}};
    construct_astres(renderer, Astres, radiusArray, distArray, colourArray, speedArray);

    /* Main Loop */
    bool hold = true;
    int delay_milliseconds = 17;
    while (hold) { 
        hold = check_event();
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        update_positions(Astres, distArray);
        place(renderer, Astres);

        SDL_RenderPresent(renderer);
        SDL_Delay(delay_milliseconds); 
    }

    quit_universe(window,renderer, Astres);
    return 0;
}
