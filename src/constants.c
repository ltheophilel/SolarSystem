#include "constants.h"

#ifdef ONSCALE
#define REDUCTION_FACTOR 150e6/28.3
const int radiusArray[NB_ASTRES] = {3, 1, 3, 3, 2, 29, 31, 10, 10};
const int distArray[NB_ASTRES] = {0, 0.4*28.3, 0.7*28.3, 1*28.3, 
    1.5*28.3, 5.2*28.3, 9.5*28.3, 19.2*28.3, 30*28.3};

#else
#define REDUCTION_FACTOR 150e6/100
const int distArray[NB_ASTRES] = {0, 0.4*100, 0.7*100, 1*100, 
    1.5*100, 2.5*100, 4*100, 5.2*100, 6*100};
const int radiusArray[NB_ASTRES] = {30, 5, 8, 8, 7, 20, 21, 13, 13};
#endif

const double massArray[NB_ASTRES] = {2e30, 6e24/20, 0.815*6e24,6e24, 
   6e24/10, 317*6e24, 95*6e24, 14*6e24, 17*6e24};