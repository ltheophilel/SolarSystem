#ifndef CONSTANTS_H
#define CONSTANTS_H

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080

#define NB_ASTRES 9
#define PI 3.1415926
#define G 6.67e-11
#define TIME_SPEEDUP 1.0e-3
#define ANGLE_NEW_YEAR 1.704273

extern const int radiusArray_arbitrary[NB_ASTRES];
extern const int distArray_arbitrary[NB_ASTRES];
extern const double reduction_arbitrary;

extern const int radiusArray_onscale[NB_ASTRES];
extern const int distArray_onscale[NB_ASTRES];
extern const double reduction_onscale;


extern const double massArray[NB_ASTRES];
extern const double yearDurationArray[NB_ASTRES];
extern const double angleArray[NB_ASTRES];

#define DAY_ANGLE 27
#define MONTH_ANGLE 8
#define YEAR_ANGLE 2025

#endif