#include "../headers/variables.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Struct for runtime variables fx. People: 10'000, Infected: 3'000
static struct stats_t * stats = NULL;

//st is a struct send as argument to what update in the current versions of stats
bool update_stats(const struct stats_t st)
{
    if (st.susceptible != 0)
        stats->susceptible = st.susceptible;

    if (st.infectious != 0)
        stats->infectious = st.infectious;

    if (st.recovered != 0)
        stats->recovered = st.recovered;
    
    if (st.recovery_rate != 0)
        stats->recovery_rate = st.recovery_rate;
        
    if (st.transmission_rate != 0)
        stats->transmission_rate = st.transmission_rate;
        
    if (st.immunity_wane != 0)
        stats->immunity_wane = st.immunity_wane;
        
    if (st.duration != 0)
        stats->duration = st.duration;
        
    if (st.R_t != 0)
        stats->R_t = st.R_t;
}

void zero_stat(const struct stats_t st)
{
    if (st.susceptible == 1)
        stats->susceptible = 0;

    if (st.infectious == 1)
        stats->infectious = 0;

    if (st.recovered == 1)
        stats->recovered = 0;
    
    if (st.recovery_rate == 1)
        stats->recovery_rate = 0;
        
    if (st.transmission_rate == 1)
        stats->transmission_rate = 0;
        
    if (st.immunity_wane == 1)
        stats->immunity_wane = 0;
        
    if (st.duration == 1)
        stats->duration = 0;
        
    if (st.R_t == 1)
        stats->R_t = 0;
}

//DO NOT FREE!!!
const struct stats_t * const read_stats()
{
    return stats;
}

//st is the input 
struct stats_t reset_stats()
{
    stats = calloc(1, sizeof(struct stats_t) );
}