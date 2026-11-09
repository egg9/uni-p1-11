#include "variables.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct snapshot_t
{
    stats_t stats;
    struct snapshot_t *prev;
};

bool initialize_snapshot();
bool create_snapshot(stats_t st);
bool generate_csv(char *path, char *filename);
void print_graph(int size);
void free_snapshots();