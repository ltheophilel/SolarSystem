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
    SDL_Surface *screen = NULL;
    const char title[] = "Universe";
    create_window(&window, title, SDL_WINDOW_SHOWN);
    screen = SDL_GetWindowSurface(window);

    /* Astres Creation */

    Astre Astres[NB_ASTRES];

    const int radiusArray[NB_ASTRES] = {40, 5, 10, 10, 8, 25, 20, 16, 16};
    Uint8 colourArray[NB_ASTRES][3] = {{255, 255, 255}, 
    {200, 200, 200}, {220, 230, 160}, {127, 127, 255}, {255, 127, 127},
    {255, 255, 220}, {255, 255, 127}, {127, 255, 210}, {50, 50, 255}};
    const int distArray[NB_ASTRES] = {0, DIST_MERCURY, DIST_VENUS, DIST_EARTH, 
    DIST_MARS, DIST_JUPITER, DIST_SATURN, DIST_URANUS, DIST_NEPTUNE};

    construct_astres(Astres, radiusArray, distArray, colourArray);
    
    /* Placement */
    place(window, screen, Astres);

    pause();

    quit_universe(window, Astres);
    return 0;
}


void pause() {
    int go_on = 1;
    SDL_Event event;
    while (go_on) {
        SDL_WaitEvent(&event);
        switch(event.type) {
            case SDL_QUIT:
                go_on = 0;
        }
    }
}
