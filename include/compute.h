#ifndef COMPUTE_H
#define COMPUTE_H
#include <stdbool.h>

#include "constants.h"
#include "compute.h"
#include "display.h"
#include "main.h"

void initial_speed_kinematics(Astre *Astres, const int distArray[NB_ASTRES]);

void initial_speed_dynamics(Astre *Astres, const int distArray[NB_ASTRES], double reduction_factor, int on_scale);

double norm2(double a, double b);

double compute_distance_inv_cubed(Astre A1,Astre A2, double reduction_factor);

void update_positions_kinematics(Astre *Astres, const int *distArray, double reduction_factor);

void update_positions_dynamics(Astre *Astres, const int *distArray, double reduction_factor);



#endif