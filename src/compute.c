// COMPUTE
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

#include "constants.h"
#include "compute.h"
#include "main.h"


void second_law_kepler(Astre *Astres) {
    for (int i = 1; i < NB_ASTRES ; i++) {
        Astre *a = &Astres[i];
        double dx = a->x - WINDOW_WIDTH / 2;
        double dy = a->y - WINDOW_HEIGHT / 2;
        double r_simu = norm2(dx, dy);
        double r = r_simu*REDUCTION_FACTOR;
        double speed = -2*PI*r_simu/sqrt(r*r*r*4*PI/(G*massArray[0]));
        a->vx = speed*cos(a->angle);
        a->vy = -speed*sin(a->angle);
        printf("VITESSE %e\n", speed);
    }
}


bool is_in_disk(int x, int y, int radius) {
    int dist_x = x-radius;
    int dist_y = y-radius;
    return ((dist_x)*(dist_x) + (dist_y)*(dist_y) <= radius*radius);
}


SDL_Texture* create_disk(SDL_Renderer *renderer,
                         int radius,
                         Uint8 red, Uint8 green, Uint8 blue)
{
    int diameter = 2 * radius;
    SDL_Surface *surface = SDL_CreateRGBSurfaceWithFormat(0, diameter, diameter, 32, SDL_PIXELFORMAT_RGBA8888);

    SDL_SetSurfaceBlendMode(surface, SDL_BLENDMODE_NONE);
    if (SDL_MUSTLOCK(surface)) SDL_LockSurface(surface);

    Uint32 color = SDL_MapRGBA(surface->format, red, green, blue, 255);  // opaque
    Uint8 *pixels = (Uint8 *)surface->pixels;
    int pitch = surface->pitch;

    for (int x = 0; x < diameter; ++x) {
        for (int y = 0; y < diameter; ++y) {
            if (is_in_disk(x, y, radius)) {
                Uint32 *pixelPtr = (Uint32 *)(pixels + y * pitch + x * 4); // 4 bytes per pixel (RGBA8888)
                *pixelPtr = color;
            }
        }
    }

    if (SDL_MUSTLOCK(surface)) SDL_UnlockSurface(surface);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);

    SDL_FreeSurface(surface);
    return texture;
}


double norm2(double a, double b) {
    return sqrt(a*a + b*b);
}


void update_positions(Astre *Astres, const int *distArray) {
    for (int i = 1 ; i < NB_ASTRES ; i++) { // Uniform Circular Mouvement
        Astre *a = &Astres[i];
        // double diffx = a->x;
        // double diffy = a->y;
        a->angle += norm2(a->vx, a->vy)/distArray[i]*1; // dt = 1 ms
        a->x = distArray[i]*cos(a->angle) + WINDOW_WIDTH/2;
        a->y = -distArray[i]*sin(a->angle) + WINDOW_HEIGHT/2;
/*         diffx -= a->x;
        diffy -= a->y;
        printf("DPOS = %e\n", norm2(diffx, diffy)); */
    }
}

double compute_distance_inv_cubed(Astre A1,Astre A2) {
    double dx = (A1.x-A2.x)*REDUCTION_FACTOR;
    double dy = (A1.y-A2.y)*REDUCTION_FACTOR;
    double sq_root = norm2(dx,dy); // Can be optimised
    return 1/(sq_root*sq_root*sq_root); // Invert w/ previous line
}



void update_positions_dynamics(Astre *Astres) {
    float dt = 0.01F;
    for (int i = 1 ; i < NB_ASTRES ; i++) {
        Astre *a = &Astres[i];
        double acceleration_sum_x = 0;
        double acceleration_sum_y = 0;
        for (int j = 1 ; j < NB_ASTRES ; j++) {
            if (i!=j) {
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
    printf("delta_pos = %e\n", norm2(a->vx*dt, a->vy*dt));
    }
}
