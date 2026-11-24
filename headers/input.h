#ifndef INPUT_H
#define INPUT_H

#include <stdio.h> // Fjern i fremtiden fordi main.c alligevel har dette library inkluderet
#include "variables.h" // Overvej om denne også skal fjernes hvis main alligevel har dette library

bool InputFirstDay(stats_t *day_one_stats, stats_const_t *day_one_stats_const);

//x = false and y = true
int input_grid_size(bool x_or_y); 

#endif