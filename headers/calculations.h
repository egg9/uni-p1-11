#ifndef CALCULATIONS_H
#define CALCULATIONS_H

#include <stdio.h> // Fjern i fremtiden fordi main.c alligevel har dette library inkluderet
#include "variables.h" // Overvej om denne også skal fjernes hvis main alligevel har dette library


void CalcNextDay(stats_t *town_stats, stats_const_t st_const);

stats_t f(stats_t st, stats_const_t st_const);

stats_t RungeKutta(stats_t st, stats_const_t st_const, double h);

#endif