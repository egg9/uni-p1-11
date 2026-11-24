#include "variables.h"


enum OVERRIDE
{
    EMPTY = 0,
    OVERRIDE = 1
};

bool check_stats(const stats_t src)
{
    // clang-format off
    if (src.susceptible < 0)         return false;
    if (src.infectious < 0)          return false;
    if (src.recovered < 0)           return false;
    if (src.R_t < 0)                 return false;
    // clang-format on
    return true;
}
bool check_stats_const(const stats_const_t src){
    // clang-format off
    if (src.transmission_rate < 0)   return false;
    if (src.immunity_wane < 0)       return false;
    if (src.duration < 1)            return false;
    // clang-format on
    return true;
}

// This function return a pointer and gives the onwership of it away
stats_t *create_stats(const stats_t src)
{
    if (!check_stats(src))
        return false;

    stats_t *ret = calloc(1, sizeof(stats_t));
    if (!ret)
    {
        fprintf(stderr, "Can't reserve enough space for the stats struct");
        exit(1);
        return NULL;
    }

    memcpy(ret, &src, sizeof(stats_t));

    return ret;
}

stats_const_t *create_stats_const(const stats_const_t src)
{
    if (!check_stats_const(src))
        return false;

    stats_const_t *ret = calloc(1, sizeof(stats_const_t));
    if (!ret)
    {
        fprintf(stderr, "Can't reserve enough space for the stats struct");
        exit(1);
        return NULL;
    }

    memcpy(ret, &src, sizeof(stats_const_t));

    return ret;
}

bool update_stats(stats_t *dst, const stats_t src)
{
    if (!check_stats(src))
        return false;

    // clang-format off
    if (src.susceptible != EMPTY)        dst->susceptible = src.susceptible;
    if (src.infectious != EMPTY)         dst->infectious = src.infectious;
    if (src.recovered != EMPTY)          dst->recovered = src.recovered;
    if (src.R_t != EMPTY)                dst->R_t = src.R_t;
    // clang-format on

    return true;
}

bool update_stats_const(stats_const_t *dst, const stats_const_t src)
{
    if (!check_stats_const(src))
        return false;

    // clang-format off
    if (src.transmission_rate != EMPTY)  dst->transmission_rate = src.transmission_rate;
    if (src.immunity_wane != EMPTY)      dst->immunity_wane = src.immunity_wane;
    if (src.duration != EMPTY)           dst->duration = src.duration;
    // clang-format on

    return true;
}

void zero_stats(stats_t *dst, const stats_t src)
{
    // clang-format off
    if (src.susceptible == OVERRIDE)        dst->susceptible = 0;
    if (src.infectious == OVERRIDE)         dst->infectious = 0;
    if (src.recovered == OVERRIDE)          dst->recovered = 0;
    if (src.R_t == OVERRIDE)                dst->R_t = 0;
    // clang-format on
}

void zero_stats_const(stats_const_t *dst, const stats_const_t src)
{
    // clang-format off
    if (src.transmission_rate == OVERRIDE)  dst->transmission_rate = 0;
    if (src.immunity_wane == OVERRIDE)      dst->immunity_wane = 0;
    if (src.duration == OVERRIDE)           dst->duration = 0;
    // clang-format on
}


bool free_stats(stats_t *src)
{
    if (src)
    {
        free(src);
        return true;
    }

    return false;
}

bool free_stats_const(stats_const_t *src)
{
    if (src)
    {
        free(src);
        return true;
    }

    return false;
}