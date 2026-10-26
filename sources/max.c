#include "../headers/max.h"
#include <stdbool.h>

// Struct for runtime variables fx. People: 10'000, Infected: 3'000
struct stats stats = {};

bool update_stats(const struct stats *ptr)
{
    if (ptr->people != 0)
        stats.people = ptr->people;
    if (ptr->susceptible != 0)
        stats.susceptible = ptr->susceptible;
    if (ptr->infected != 0)
        stats.infected = ptr->infected;
    if (ptr->immune != 0)
        stats.immune = ptr->immune;
    if (ptr->dead != 0)
        stats.dead = ptr->dead;
}
void zero_stat(const struct stats *ptr)
{
    if (ptr->people == 1)
        stats.people = 0;
    if (ptr->susceptible == 1)
        stats.susceptible = 0;
    if (ptr->infected == 1)
        stats.infected = 0;
    if (ptr->immune == 1)
        stats.immune = 0;
    if (ptr->dead == 1)
        stats.dead = 0;
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