#include "weather.h"
#include "array_helpers.h"


int min_temp(WeatherTable a){
    int min;
    min = a[0][0][0]._min_temp;
    for (unsigned int year = 0u; year < YEARS; ++year) {
        for (month_t month = january; month <= december; ++month) {
            for (unsigned int day = 0u; day < DAYS; ++day) {
                if (a[year][month][day]._min_temp < min){
                    min = a[year][month][day]._min_temp;
                }
            }
        }
    }
    return min;
}

void max_temp_year(WeatherTable a, int output[YEARS]){
    int max;
    for (unsigned int year = 0; year < YEARS; year++) {
        max = 0;
        for (month_t month = january; month <= december; ++month) {           
            for (unsigned int day = 0u; day < DAYS; ++day) {
                if (a[year][month][day]._max_temp > max){
                    output[year] = a[year][month][day]._max_temp;
                }
            }
        }
}
}

void max_temp_month(WeatherTable a, int output[YEARS]){
    unsigned int maxPrec, prec;
    month_t maxMonth;
    for (unsigned int year = 0; year < YEARS; year++) {
        maxMonth = january;
        maxPrec = 0u;
        for (month_t month = january; month <= december; ++month) {   
            prec = 0u;        
            for (unsigned int day = 0u; day < DAYS; ++day) {
                if (a[year][month][day]._rainfall > prec){
                    prec = prec + a[year][month][day]._rainfall;
                }
            }
            if (maxPrec < prec){
                maxPrec = prec;
                maxMonth = month;
                output[year] = maxMonth;
            }
        }
}
}