/**
 * @file compute.c
 * @author Theophile (ltheophilel on GitHub)
 * @brief computing functions : astre shape & computing next positions
 * @version 0.3
 * @date 2025-08-27
 *
 * @copyright Copyright (c) 2025
 *
 */
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

#include "constants.h"
#include "compute.h"
#include "main.h"

/**
 * @brief Computes the initial velocities of the planets using
 * Kepler's scond law.
 *
 * @param Astres array of Astres.
 */
void second_law_kepler(Astre *Astres) 
{
    for (int i = 1; i < NB_ASTRES ; i++) 
    {
        Astre *a = &Astres[i];
        double dx = a->x - WINDOW_WIDTH / 2;
        double dy = a->y - WINDOW_HEIGHT / 2;
        double r_simu = norm2(dx, dy);
        double r = r_simu*REDUCTION_FACTOR;
        double speed = -2*PI*r_simu/sqrt(r*r*r*4*PI/(G*massArray[0]));
        a->vx = speed*cos(a->angle);
        a->vy = -speed*sin(a->angle);
        // printf("VITESSE %e\n", speed);
    }
}

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
    SDL_Surface *surface = SDL_CreateRGBSurfaceWithFormat(0, diameter, diameter, 32, SDL_PIXELFORMAT_RGBA8888);

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

/**
 * @brief Compute the norm 2 of a vector
 *
 * @param x coordinate
 * @param y coordinate
 * @return double distance
 */
double norm2(double x, double y)
{
    return sqrt(x*x + y*y);
}

/**
 * @brief Compute the next positions for planets 
 * in kinematics mode : Uniform Circular Mouvement
 *
 * @param Astres 
 * @param distArray 
 */
void update_positions(Astre *Astres, const int *distArray) 
{
    double dt = 1.0F;
    for (int i = 1 ; i < NB_ASTRES ; i++) 
    { // Uniform Circular Mouvement
        Astre *a = &Astres[i];
        a->angle += norm2(a->vx, a->vy)/distArray[i] *dt;
        a->x = distArray[i]*cos(a->angle) + WINDOW_WIDTH/2;
        a->y = -distArray[i]*sin(a->angle) + WINDOW_HEIGHT/2;
    }
}

/**
 * @brief Compute 1/dist^3 between 2 astres
 *
 * @param A1 Astre 1
 * @param A2 Astre 2
 * @return double result
 */
double compute_distance_inv_cubed(Astre A1,Astre A2) 
{
    double dx = (A1.x-A2.x)*REDUCTION_FACTOR;
    double dy = (A1.y-A2.y)*REDUCTION_FACTOR;
    double sq_root = norm2(dx,dy); // Can be optimised
    return 1/(sq_root*sq_root*sq_root); // Invert w/ previous line
}

/**
 * @brief Compute the next positions for planets 
 * in dynamics mode
 *
 * @param Astres 
 */
void update_positions_dynamics(Astre *Astres, const int *distArray) 
{
    float dt = 0.01F;
    for (int i = 1 ; i < NB_ASTRES ; i++) 
    {
        Astre *a = &Astres[i];
        double acceleration_sum_x = 0;
        double acceleration_sum_y = 0;
        for (int j = 1 ; j < NB_ASTRES ; j++) 
        {
            if (i!=j) 
            {
                double common_part = massArray[j]*compute_distance_inv_cubed(Astres[i],Astres[j]);
                acceleration_sum_x += common_part*(Astres[j].x-Astres[i].x)*REDUCTION_FACTOR;
                acceleration_sum_y += common_part*(Astres[j].y-Astres[i].y)*REDUCTION_FACTOR;
                // printf("%f\n", acceleration_sum_x);
            }
        }
        double acc_factor = 0.5*G*dt;
        a->vx += acceleration_sum_x*acc_factor;
        a->vy += acceleration_sum_y*acc_factor;
        a->x += a->vx*dt*10;
        a->y += a->vy*dt*10;
        // printf("delta_pos = %e\n", norm2(a->vx*dt, a->vy*dt));
    }
}
