#include <stdbool.h>


// Struct for runtime variables fx. People: 10'000, Infected: 3'000
struct stats
{
    int susceptible; //totals
    int infectious;  //totals
    int recovered;   //totals
    //
    double recovery_rate; // =1/duration \gamma
    double transmission_rate; // \beta
    double immunity_wane; // how long does immunity last \xi
    //
    int duration; //const how many days a person is sick
    double R_t; // effetive repreductive number    =recovery_rate
    const double R_0; // const
    const int total_days; //const
    
};

bool update_stats(const struct stats st);
void zero_stat(const struct stats st);
const struct stats * const read_stats();
struct stats reset_stats();
// END
