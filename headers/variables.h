#ifndef VARIABLES_H
#define VARIABLES_H

#include <stdbool.h>

// Struct for runtime variables fx. People: 10'000, Infected: 3'000
// per section of a town/grid
typedef struct
{
    double susceptible; // totals
    double infectious;  // totals
    double recovered;   // totals

    double R_t; // effetive repreductive number    =recovery_rate
} stats_t;

// per town
typedef struct
{
    double recovery_rate;     // =1/duration \gamma
    double transmission_rate; // \beta
    double immunity_wane;     // how long does immunity last \xi

    int duration; // const how many days a person is sick
} stats_const_t;

// Use to set all the variables of stats 
//primary use is for overriding or creation
stats_t *create_stats(const stats_t src);
stats_const_t *create_stats_const(const stats_const_t src);

// Used internally to validate if the change is allowed
bool check_stats(const stats_t src);
bool check_stats_const(const stats_const_t src);

// Use this to update value in the stats_t struct for validation
bool update_stats(stats_t *dst, const stats_t src);
bool update_stats_const(stats_const_t *dst, const stats_const_t src);

// Use this if you want to zero a value in the struct
void zero_stats(stats_t *dst, const stats_t src);
void zero_stats_const(stats_const_t *dst, const stats_const_t src);

bool free_stats(stats_t *src);
bool free_stats_const(stats_const_t *src);

#endif
