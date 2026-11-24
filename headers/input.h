#ifndef INPUT_H
#define INPUT_H

#include <stdio.h> // Fjern i fremtiden fordi main.c alligevel har dette library inkluderet
#include "variables.h" // Overvej om denne også skal fjernes hvis main alligevel har dette library

stats_t InputFirstDay();

//x = false and y = true
int input_grid_size(bool x_or_y); 

#endif