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
} stats_t;

bool create_stats(const stats_t st); // Use to set all the variables of stats (including const) //primary use is for overriding or creation
bool check_stats(const stats_t st);  // Used internally to validate if the change is allowed
bool update_stats(const stats_t st); // Use this to update value in the stats_t struct for validation
void zero_stats(const stats_t st);   // Use this if you want to zero a value in the struct
const stats_t *const read_stats();   // Returns a const pointer to stats and nothing can be changed

#endif
