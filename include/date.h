#ifndef DATE_H
#define DATE_H

#include <math.h>
#include <stdbool.h>

#include "constants.h"
#include "compute.h"
#include "main.h"

void get_date(
    int *year,
    int *month,
    int* day);

void get_today_angles(
    double today_angles[NB_ASTRES]);

int compute_year(
    Astre Earth,
    int *new_year);

#endif
