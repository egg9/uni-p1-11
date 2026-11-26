#ifndef SNAPSHOT_H
#define SNAPSHOT_H

#include "variables.h"
#include "grid.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <time.h>



typedef struct snapshot_t
{
    grid_t grid;
    struct snapshot_t *prev;
} snapshot_t;

snapshot_t * initialize_snapshot(grid_t grid);
bool create_snapshot(snapshot_t ** linked_list, grid_t grid);
bool generate_csv(const snapshot_t * linked_list);
bool free_snapshots(snapshot_t * linked_list);
bool check_snapshot(const snapshot_t linked_list);

#endif