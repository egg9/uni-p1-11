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

stats_t get_stat_from_grid(grid_t *grid, int x, int y)
{
    return grid->stats[y * grid->x_size + x];
}

bool initialize_grid(grid_t *grid, stats_t src, const stats_const_t src2)
{
    if (!check_stats(src))
    {
        return false;
    }

    if (!check_stats_const(src2))
    {
        return false;
    }

    if (!grid)
    {
        return false;
    }

    memcpy(grid->stats, &src, sizeof(stats_t));          // copy stats to the first cell
    zero_stats(&src, (stats_t){.infectious = OVERRIDE}); // override stats.infectious til 0

    for (int index = 1; index < grid->x_size * grid->y_size; ++index)
    {
        // memory copy
        // overriden stats gets copied to every cell
        memcpy(grid->stats + index, &src, sizeof(stats_t));
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
    if (!check_stats_const(grid.stats_const))
    {
        return false;
    }
    if (grid.x_size < 1 && grid.y_size < 1)
    {
        return false;
    }

    return true;
}

void copy_grid(grid_t *dst, const grid_t *src) {
    dst = create_grid(src->x_size, src->y_size);
    memcpy(dst->stats, src->stats, sizeof(src->stats));
    dst->stats_const = src->stats_const;
    
    return;
}