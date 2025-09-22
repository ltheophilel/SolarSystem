#ifndef CONSTANTS_H
#define CONSTANTS_H

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080

#define NB_ASTRES 9
#define PI 3.1415926
#define G 6.67e-11
#define TIME_SPEEDUP 1
#define ANGLE_NEW_YEAR 1.704273

extern const int radiusArray[NB_ASTRES];
extern const int distArray[NB_ASTRES];
extern const double massArray[NB_ASTRES];
extern const double yearDurationArray[NB_ASTRES];
extern const double angleArray[NB_ASTRES];

#ifdef ONSCALE
#define REDUCTION_FACTOR 150e6/28.3
#else
#define REDUCTION_FACTOR 150e6/100
#endif

#define DAY_ANGLE 27
#define MONTH_ANGLE 8
#define YEAR_ANGLE 2025

#endif