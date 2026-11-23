#include "grid.h"

// returns a pointer to the created and reserved memory
// ownership of the pointer get transferred to the caller
grid_t *create_grid(const int x_size, const int y_size)
{
    if (x_size < 1 || y_size < 1)
        return NULL;

    grid_t *grid = calloc(1, sizeof(grid_t));
    if (!grid)
    {
        fprintf(stderr, "Can't reserve enough space for a grid struct");
        exit(1);
        return NULL;
    }

    grid->stats = calloc(x_size * y_size, sizeof(stats_t));
    if (!grid->stats)
    {
        fprintf(stderr, "Can't reserve enough space for the grid struct pool");
        free(grid);
        exit(1);
        return NULL;
    }

    grid->x_size = x_size;
    grid->y_size = y_size;

    return grid;
}

bool initialize_grid(grid_t *grid, const stats_t src, const stats_const_t src2)
{
    if (check_stats(src))
    {
        return false;
    }

    for (int i = 0; i < grid->x_size * grid->y_size; ++i)
    {
        // memory copy
        memcpy(grid->stats + i, &src, sizeof(stats_t));
    }

    grid->stats_const = src2;

    return true;
}

bool free_grid(grid_t *grid)
{
    if (grid)
    {
        free(grid->stats);
        free(grid);
        return true;
    }
    return false;
}

bool check_grid(const grid_t grid)
{
    if (!grid.stats)
    {
        return false;
    }
    if (!grid.stats_const)
    {
        return false;
    }
    if (grid.x_size < 1 && grid.y_size < 1)
    {
        return false;
    }

    return true;
}