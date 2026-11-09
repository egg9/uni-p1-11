#include "../headers/variables.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Struct for runtime variables fx. People: 10'000, Infected: 3'000
static stats_t *stats = NULL;

#include <stdio.h>

bool check_stats(const stats_t st)
{
    // clang-format off
    if (st.susceptible < 0)         return false;
    if (st.infectious < 0)          return false;
    if (st.recovered < 0)           return false;
    if (st.transmission_rate < 0)   return false;
    if (st.immunity_wane < 0)       return false;
    if (st.duration < 0)            return false;
    if (st.R_t < 0)                 return false;
    // clang-format on
    return true;
}

bool create_stats(const stats_t st)
{
    if (!check_stats(st))
        return false;

    if (stats != NULL)
        free(stats);

    stats = calloc(1, sizeof(stats_t));
    if (!stats)
    {
        fprintf(stderr, "Can't reserve enough space for the stats struct");
        exit(1);
        return false;
    }

    memcpy(stats, &st, sizeof(stats_t));

    return true;
}
// st is a struct send as argument to what update in the current versions of stats
#include <stdio.h>

bool update_stats(const stats_t st)
{
    if (!check_stats(st))
        return false;

    // clang-format off
    if (st.susceptible != 0)        stats->susceptible = st.susceptible;
    if (st.infectious != 0)         stats->infectious = st.infectious;
    if (st.recovered != 0)          stats->recovered = st.recovered;
    if (st.transmission_rate != 0)  stats->transmission_rate = st.transmission_rate;
    if (st.immunity_wane != 0)      stats->immunity_wane = st.immunity_wane;
    if (st.duration != 0)           stats->duration = st.duration;
    if (st.R_t != 0)                stats->R_t = st.R_t;
    // clang-format on

    return true;
}

void zero_stats(const stats_t st)
{
    // clang-format off
    if (st.susceptible == 1)        stats->susceptible = 0;
    if (st.infectious == 1)         stats->infectious = 0;
    if (st.recovered == 1)          stats->recovered = 0;
    if (st.transmission_rate == 1)  stats->transmission_rate = 0;
    if (st.immunity_wane == 1)      stats->immunity_wane = 0;
    if (st.duration == 1)           stats->duration = 0;
    if (st.R_t == 1)                stats->R_t = 0;
    // clang-format on
}

// DO NOT FREE!!!
const stats_t *const read_stats()
{
    return stats;
}
