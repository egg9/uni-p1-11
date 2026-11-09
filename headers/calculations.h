#include <stdio.h> // Fjern i fremtiden fordi main.c alligevel har dette library inkluderet
#include "variables.h" // Overvej om denne også skal fjernes hvis main alligevel har dette library


void CalcNextDay(stats_t st);

stats_t f(stats_t st);

stats_t RungeKutta(stats_t st, double h);