#ifndef VARIABLES_H
#define VARIABLES_H

#include <stdbool.h>


// Struct for runtime variables fx. People: 10'000, Infected: 3'000
typedef struct
{
    double susceptible; // totals
    double infectious;  // totals
    double recovered;   // totals
    
    double recovery_rate;     // =1/duration \gamma
    double transmission_rate; // \beta
    double immunity_wane;     // how long does immunity last \xi
    
    int duration; // const how many days a person is sick
    double R_t;   // effetive repreductive number    =recovery_rate
} stats_t;

// Use to set all the variables of stats //primary use is for overriding or creation
stats_t * create_stats(const stats_t src); 

// Used internally to validate if the change is allowed
bool check_stats(const stats_t src);  

// Use this to update value in the stats_t struct for validation
bool update_stats(stats_t * dst, const stats_t src); 

// Use this if you want to zero a value in the struct
void zero_stats(stats_t * dst, const stats_t src);   

// Returns a const pointer to stats and nothing can be changed
const stats_t read_stats(stats_t * src);        

bool free_stats(stats_t * src);

#endif
