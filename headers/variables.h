#include <stdbool.h>
#ifndef VARIABLES_H
#define VARIABLES_H

// Struct for runtime variables fx. People: 10'000, Infected: 3'000
typedef struct
{
    int susceptible; // totals
    int infectious;  // totals
    int recovered;   // totals
    //
    double recovery_rate;     // =1/duration \gamma
    double transmission_rate; // \beta
    double immunity_wane;     // how long does immunity last \xi
    //
    int duration;         // const how many days a person is sick
    double R_t;           // effetive repreductive number    =recovery_rate
    const double R_0;     // const
    const int total_days; // const
} stats_t;

bool update_stats(const stats_t st); //Use this to update value in the stats_t struct for validation
void zero_stat(const stats_t st);    //Use this if you want to zero a value in the struct
const stats_t *const read_stats();
stats_t *reset_stats();

#endif
