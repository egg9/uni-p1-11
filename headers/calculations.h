#include <stdio.h> // Fjern i fremtiden fordi main.c alligevel har dette library inkluderet
#include "variables.h" // Overvej om denne også skal fjernes hvis main alligevel har dette library


void CalcNextDay(stats_t st);

double f(double x, double y);

double RungeKutta(double x_0, double y_0, double x, double h);