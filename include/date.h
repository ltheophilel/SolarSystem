#ifndef DATE_H
#define DATE_H
#include <stdbool.h>

#include "constants.h"
#include "compute.h"
#include "display.h"
#include "main.h"

void get_date(int *year, int *month, int* day);

int days_past(int year, int month, int day);

void get_today_angles(double today_angles[NB_ASTRES]);

int compute_year(Astre Earth, int *new_year);

#endif