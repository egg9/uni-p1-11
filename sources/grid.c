#include "grid.h"

// returns a pointer to the created and reserved memory
// ownership of the pointer get transferred to the caller
grid_t *create_grid(const int x_size, const int y_size)
{
    if (x_size < 1 || y_size < 1)
        return NULL;

    grid_t *grid = calloc(1, sizeof(grid_t));
    if (!grid) {
        fprintf(stderr, "Can't reserve enough space for a grid struct");
        exit(1);
        return NULL;
    }

    grid->stats = calloc(x_size*y_size, sizeof(struct stats_t));
    if (!grid->stats) {
        fprintf(stderr, "Can't reserve enough space for the grid struct pool");
        free(grid);
        exit(1);
        return NULL;
    }

    grid->x_size = x_size;
    grid->y_size = y_size;

    return grid;
}

bool initialize_grid(grid_t *grid, const struct stats_t src) {
    if ( check_stats(src) ) {
        return false;
    }

    for (int i = 0; i < grid->x_size*grid->y_size; ++i) {
        grid->stats[i] = src;
    }

    return true;
}

bool free_grid(grid_t *grid) {
    if (grid) {
        free(grid);
        return true;
    }
    return false;
}