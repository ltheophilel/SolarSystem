#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "constants.h"
#include "display.h"


void pause();

int main() 
{
    sdl_init();
    SDL_Window *window = NULL;
    SDL_Surface *screen = NULL;
    const char title[] = "Universe";
    create_window(&window, title, SDL_WINDOW_SHOWN);

    screen = SDL_GetWindowSurface(window);
    const int RECTANGLE_WIDTH = WINDOW_WIDTH/2;
    const int RECTANGLE_HEIGHT = WINDOW_HEIGHT/2;

    SDL_Surface *rectangle = NULL;
    create_rectangle(screen, &rectangle,
                    RECTANGLE_WIDTH, RECTANGLE_HEIGHT);

    place_centered(window, screen, rectangle, 
                RECTANGLE_WIDTH, RECTANGLE_HEIGHT);
    pause();
    SDL_FreeSurface(rectangle);
    SDL_DestroyWindow(window);
    SDL_Quit();
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