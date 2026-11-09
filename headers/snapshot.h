#include "variables.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct Snapshot
{
    stats_t stats;
    struct Snapshot *next;
};

bool create_snapshot();
bool add_snapshot(stats_t st);
bool generate_csv(char *path, char *filename);