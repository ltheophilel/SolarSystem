#ifndef COMPUTE_H
#define COMPUTE_H
#include <stdbool.h>
#include <math.h>

#include "constants.h"
#include "main.h"

void initial_speed_kinematics(Astre *Astres, const int distArray[NB_ASTRES]);

void initial_speed_dynamics(Astre *Astres, const int distArray[NB_ASTRES], double reduction_factor, int on_scale);

void update_positions_kinematics(Astre *Astres, const int *distArray, double reduction_factor);

void update_positions_dynamics(Astre *Astres, const int *distArray, double reduction_factor);



#endif
