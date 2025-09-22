#ifndef COMPUTE_H
#define COMPUTE_H
#include <stdbool.h>

#include "constants.h"
#include "compute.h"
#include "display.h"
#include "main.h"

void second_law_kepler(Astre *Astres);

void initial_speed(Astre *Astres);

void get_date(int *year, int *month, int* day);

int days_past(int year, int month, int day);

void get_today_angles(double today_angles[NB_ASTRES]);

bool is_in_disk(int x, int y, int radius, int i);

bool is_in_shadow(int x, int y, int planet_x, int planet_y, int radius);

SDL_Texture* create_disk(SDL_Renderer *renderer,
                        int radius, Uint8 red, Uint8 green, Uint8 blue, int i, int planet_x, int planet_y);

double norm2(double a, double b);

void update_positions(Astre *Astres, const int *distArray);

double compute_distance_inv_cubed(Astre A1,Astre A2);

void update_positions_dynamics(Astre *Astres, const int *distArray);

int compute_year(Astre Earth);

#endif