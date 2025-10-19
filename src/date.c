/**
 * @file date.c
 * @author Theophile (ltheophilel on GitHub)
 * @brief date related computing functions
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

/**
 * @brief Compute how many days separate compile time from the 2025/08/27
 *        (Date of the data collection)
 * @return
 */
void get_date(int *year, int *month, int* day)
{
    char today[] = __DATE__;
    // printf("%s\n", today);

    char all_months[] = "JanFebMarAprMayJunJulAugSepOctNovDec";
    char today_month[4];
    strncpy(today_month, today, 3);
    today_month[3] = '\0';

    for (int k = 0; k < 12; k++) 
    {
        char month_test[4];
        strncpy(month_test, all_months + 3*k, 3);
        month_test[3] = '\0';
        if (strcmp(today_month, month_test) == 0) 
        {
            *month = k + 1;
            break;
        }
    }
    if (today[4]==' ') *day = (today[5]-'0');
    else *day = 10*(today[4]-'0') + (today[5]-'0');
    *year = 1000*(today[7]-'0')+ 100*(today[8]-'0')+10*(today[9]-'0')+(today[10]-'0');
}

/**
 * @brief 
 * 
 * @param year 
 * @param month 
 * @param day 
 * @return int 
 */
int days_past(int year, int month, int day)
{
    int diff_years = (year-YEAR_ANGLE)*365;
    int diff_months = (month-MONTH_ANGLE)*30;
    int diff_days = day-DAY_ANGLE;
    // printf("%d", diff_days+diff_months+diff_years);
    return diff_days+diff_months+diff_years;
}

/**
 * @brief Get the today angles from the measurement on the 2025/08/27
 *
 * @param today_angles 
 */
void get_today_angles(double today_angles[NB_ASTRES])
{
    int year, month, day;
    get_date(&year, &month, &day);
    int nb_days = days_past(year, month, day);
    for (int i = 0 ; i < NB_ASTRES ; i++)
        today_angles[i] = angleArray[i] + (nb_days/yearDurationArray[i])*2*PI;
    // printf("%lf\n", fmod(today_angles[3], 2*PI));
}

/**
 * @brief 
 * 
 * @param Earth 
 * @param current_year 
 * @return int 
 */
int compute_year(Astre Earth, int *new_year)
{
    double angle = fmod(Earth.angle, 2*PI);
    if (angle-ANGLE_NEW_YEAR > 0 && *new_year == 0)
    {
        *new_year = 1;
        return 1;
    }
    else if (angle-ANGLE_NEW_YEAR < 0 && *new_year == 1)
    {
        *new_year = 0;
    }
    return 0;
}


