#include "../headers/variables.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Struct for runtime variables fx. People: 10'000, Infected: 3'000
struct stats * stats = NULL;

//st is a struct send as argument to what update in the current versions of stats
bool update_stats(const struct stats st)
{
    if (st.susceptible != 0)
        stats->susceptible = st.susceptible;
}

void zero_stat(const struct stats st)
{

    if (st.susceptible == 1)
        stats->susceptible = 0;
}

//DO NOT FREE!!!
const struct stats * const read_stats()
{
    return stats;
}

//st is the input 
struct stats reset_stats()
{
    stats = calloc(1, sizeof(struct stats) );
}