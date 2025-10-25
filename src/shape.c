/**
 * @file shape.c
 * @author Theophile (ltheophilel on GitHub)
 * @brief computing functions : astre shapes
 * @version 0.4
 * @date 2025-10-25
 *
 */
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "constants.h"
#include "compute.h"
#include "main.h"
#include "shape.h"


/**
 * @brief returns if a pixel should be on 
 * if it is in the planet
 *
 * @param x coordinate
 * @param y coordinate
 * @param radius radius of the planet
 * @param i rank of the planet (for customising)
 * @return true if the pixel is on
 * @return false else
 */
bool is_in_disk(int x, int y, int radius, int i)
{
    int dist_x = x-radius;
    int dist_y = y-radius;
    int dist_compute = dist_x*dist_x + dist_y*dist_y;
    bool disk = (dist_compute <= radius*radius);
    bool empty; // Saturn rings
    if (i==6) empty = ((dist_compute >= 0.8*radius*0.8*radius) && (dist_compute <= 0.93*radius*0.93*radius));
    return (disk && !empty);
}

/**
 * @brief returns if a pixel should be darker if it
 * is in the shadow
 *
 * @param x coordinate
 * @param y coordinate
 * @param planet_x planet center coordinate
 * @param planet_y planet center coordinate
 * @param radius
 * @return true if the pixel should be dark
 * @return false else
 */
bool is_in_shadow(int x, int y, int planet_x, int planet_y, int radius)
{
    int dist_x = x-radius;
    int dist_y = y-radius;
    int dot_prod = planet_x*dist_x + planet_y*dist_y;
    return dot_prod > 0;
}

/**
 * @brief Create a disk object
 * 
 * @param renderer
 * @param radius
 * @param red
 * @param green
 * @param blue
 * @param i astre rank
 * @param planet_x planet center coordinate
 * @param planet_y planet center coordinate
 * @return SDL_Texture*
 */
SDL_Texture* create_disk(SDL_Renderer *renderer,
                         int radius, Uint8 red, Uint8 green, Uint8 blue,
                         int i, int planet_x, int planet_y)
{
    int diameter = 2 * radius;
    SDL_Surface *surface = SDL_CreateRGBSurfaceWithFormat(0,
        diameter, diameter, 32, SDL_PIXELFORMAT_RGBA8888);

    SDL_SetSurfaceBlendMode(surface, SDL_BLENDMODE_NONE);
    if (SDL_MUSTLOCK(surface)) SDL_LockSurface(surface);
    Uint8 *pixels = (Uint8 *)surface->pixels;
    int pitch = surface->pitch;
    Uint32 color = SDL_MapRGBA(surface->format, red, green, blue, 255);  // opaque
    Uint32 colordark = SDL_MapRGBA(surface->format, red, green, blue, 80);  // transparent
    for (int x = 0; x < diameter; ++x) 
    {
        for (int y = 0; y < diameter; ++y) 
        {
            if (is_in_disk(x, y, radius, i)) 
            {
                Uint32 *pixelPtr = (Uint32 *)(pixels + y * pitch + x * 4); // 4 bytes per pixel (RGBA8888)
                if (i == 0 || !is_in_shadow(x,y, planet_x, planet_y,radius)) *pixelPtr = color;
                else *pixelPtr = colordark;
            }
        }
    }
    if (SDL_MUSTLOCK(surface)) SDL_UnlockSurface(surface);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);

    SDL_FreeSurface(surface);
    return texture;
}
