#ifndef _WEATHER_UTILS_H
#define _WEATHER_UTILS_H

#include "weather.h"
#include "array_helpers.h"

int min_temp(WeatherTable a);

void max_temp_year(WeatherTable a, int output[YEARS]);

void max_temp_month(WeatherTable a, int output[YEARS]);

#endif