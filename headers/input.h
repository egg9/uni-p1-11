#ifndef INPUT_H
#define INPUT_H

#include <stdio.h> // Fjern i fremtiden fordi main.c alligevel har dette library inkluderet
#include "variables.h" // Overvej om denne også skal fjernes hvis main alligevel har dette library

bool InputFirstDay(stats_t *day_one_stats, stats_const_t *day_one_stats_const);

//x = false and y = true
int input_grid_size(bool x_or_y);

// Reads all the start values from a config file, returns false if the file is missing or wrong
bool load_config(const char *path, int *x_size, int *y_size, stats_t *stats, stats_const_t *stats_const);

#endif