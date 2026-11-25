#ifndef GRID_H
#define GRID_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> 

#include "variables.h"

typedef struct {

    stats_t * stats;
    stats_const_t stats_const;
    int x_size;
    int y_size;
} grid_t;

//size is how many cells should there be per axis
//creates the struct and allocates memory
grid_t * create_grid(const int x_size, const int y_size);

//grid is the refference to a struct that the operation needs to be preformed on
//src is what the total amount that will be split evenly between all the cells
//defines the struct (gives it values)
bool initialize_grid(grid_t * grid, const stats_t src, const stats_const_t src_2);

//frees memory of the struct and its children
bool free_grid(grid_t * grid);

//the same as a null check
//this function needs to check for 'correctness' of this struct
bool check_grid(const grid_t grid);

inline stats_t get_stat_from_grid(grid_t *grid, int x, int y)
#endif