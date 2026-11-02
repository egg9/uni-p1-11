#include "../headers/variables.h"
#include <stdbool.h>

// Struct for runtime variables fx. People: 10'000, Infected: 3'000
struct stats stats = {};

bool update_stats(const struct stats ptr)
{

    if (ptr.susceptible != 0)
        stats.susceptible = ptr.susceptible;
}
void zero_stat(const struct stats ptr)
{

    if (ptr.susceptible == 1)
        stats.susceptible = 0;
}
const struct stats *read_stats()
{
    return &stats;
}
void reset_stats()
{
    stats = (struct stats){};
}
// END