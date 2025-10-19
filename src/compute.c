/**
 * @file compute.c
 * @author Theophile (ltheophilel on GitHub)
 * @brief computing functions : simulation related computing
 * @version 0.3
 * @date 2025-08-27
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
#include "date.h"
#include "shape.h"

/**
 * @brief Compute the initial speed for each planet in kinematics mode
 *
 * @param Astres
 */
void initial_speed_kinematics(Astre *Astres, const int distArray[NB_ASTRES])
{
    for (int i = 1; i < NB_ASTRES ; i++) 
    {
        Astre *a = &Astres[i];
        double perimeter_amplified = 2*PI*distArray[i];
        a->vx = perimeter_amplified/yearDurationArray[i]*cos(a->angle);
        a->vy = -perimeter_amplified/yearDurationArray[i]*sin(a->angle);
        /* double speed = norm2(a->vx, a->vy);
        printf("VITESSE %e\n", speed); */
    }
}

/**
 * @brief Compute the initial speed for each planet in kinematics mode
 *
 * @param Astres
 */
void initial_speed_dynamics(Astre *Astres, const int distArray[NB_ASTRES], double reduction_factor, int on_scale)
{
    int CONVERGENCE_CONSTANT= 27*(on_scale+1) - on_scale*2;
    // if (on_scale==1) CONVERGENCE_CONSTANT= 52;
    // else CONVERGENCE_CONSTANT= 27;
    double gauss_constant = sqrt(G*massArray[0])*CONVERGENCE_CONSTANT;
    for (int i = 1; i < NB_ASTRES ; i++)
    {
        Astre *a = &Astres[i];
        double tangential_speed = gauss_constant / 
            (sqrt(distArray[i]*reduction_factor)*reduction_factor);
        a->vx = -tangential_speed*sin(a->angle);
        a->vy = -tangential_speed*cos(a->angle);
        /* double speed = norm2(a->vx, a->vy);
        printf("VITESSE %e\n", speed); */
    }
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
void update_positions_kinematics(Astre *Astres,
    const int *distArray,
    double reduction_factor __attribute__((unused))) 
{
    double dt = 1.0F;
    for (int i = 1 ; i < NB_ASTRES ; i++) 
    { // Uniform Circular Mouvement
        Astre *a = &Astres[i];
        a->angle += norm2(a->vx, a->vy)/distArray[i] *dt;
        a->x = distArray[i]*cos(a->angle) + WINDOW_WIDTH/2;
        a->y = -distArray[i]*sin(a->angle) + WINDOW_HEIGHT/2;
        /* if (i == 3)
            printf("angle = %lf\n", a->angle); */
    }
}

/**
 * @brief Compute 1/dist^3 between 2 astres
 *
 * @param A1 Astre 1
 * @param A2 Astre 2
 * @return double result
 */
double compute_distance_inv_cubed(Astre A1, Astre A2, double reduction_factor) 
{
    double dx = (A1.x-A2.x)*reduction_factor;
    double dy = (A1.y-A2.y)*reduction_factor;
    double sq_root = norm2(dx,dy); // Can be optimised
    return 1/(sq_root*sq_root*sq_root); // Invert w/ previous line
}

/**
 * @brief Compute the next positions for planets 
 * in dynamics mode
 *
 * @param Astres 
 */
void update_positions_dynamics(Astre *Astres, 
    const int *distArray __attribute__((unused)),
    double reduction_factor) 
{
    float dt = 0.1F;
    for (int i = 1 ; i < NB_ASTRES ; i++) 
    {
        Astre *a = &Astres[i];
        double acceleration_sum_x = 0;
        double acceleration_sum_y = 0;
        for (int j = 0 ; j < NB_ASTRES ; j++) 
        {
            if (i!=j)
            {
                double common_part = massArray[j]*
                compute_distance_inv_cubed(Astres[i],Astres[j], reduction_factor);

                acceleration_sum_x += common_part*(Astres[j].x-Astres[i].x)*reduction_factor;
                acceleration_sum_y += common_part*(Astres[j].y-Astres[i].y)*reduction_factor;
                // printf("%f\n", acceleration_sum_x);
            }
        }
        double acc_factor = 0.5*G*dt*TIME_SPEEDUP;
        a->vx += acceleration_sum_x*acc_factor;
        a->vy += acceleration_sum_y*acc_factor;
        a->x += a->vx*dt;
        a->y += a->vy*dt;
        a->angle = atan2(-(a->y-WINDOW_HEIGHT/2), a->x-WINDOW_WIDTH/2);
        /* if (i == 3)
            printf("angle = %lf\n", a->angle); */
    }
}

