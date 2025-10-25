#include "constants.h"

const double reduction_onscale = 150e6/28.3;
const int radiusArray_onscale[NB_ASTRES] = {3, 1, 3, 3, 2, 29, 31, 10, 10};
const int distArray_onscale[NB_ASTRES] = {0, 0.4*28.3, 0.7*28.3, 1*28.3, 
    1.5*28.3, 5.2*28.3, 9.5*28.3, 19.2*28.3, 30*28.3};

const double reduction_arbitrary = 150e6/100;
const int radiusArray_arbitrary[NB_ASTRES] = {30, 8, 13, 13, 11, 29, 31, 20, 20};
const int distArray_arbitrary[NB_ASTRES] = {0, 0.4*100, 0.7*100, 1*100, 
    1.5*100, 2.5*100, 4*100, 5.2*100, 6*100};

const double massArray[NB_ASTRES] = {2e30, 6e24/20, 0.815*6e24,6e24, 
    6e24/10, 317*6e24, 95*6e24, 14*6e24, 17*6e24};

const double yearDurationArray[NB_ASTRES] = {1, 88, 225, 365,
    687, 4333, 10756, 30689, 60195};

const double angleArray[NB_ASTRES] = {
0,
1.34407805696083,
1.27653381490865,
5.83568288696824,
3.75978827464619,
1.7242107680452	,
6.23745768077734,
1.01979588194029,
0.012915436464758};
