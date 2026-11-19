#include "variables.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <time.h>

#ifndef SNAPSHOT_H
#define SNAPSHOT_H

struct snapshot_t
{
    stats_t stats;
    struct snapshot_t *prev;
};

struct snapshot_t * initialize_snapshot(stats_t st);
bool create_snapshot(struct snapshot_t * linked_list, stats_t st);
bool generate_csv(struct snapshot_t * linked_list);
bool free_snapshots(struct snapshot_t * linked_list);

#endif