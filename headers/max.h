#include <stdbool.h>

// Struct for runtime variables fx. People: 10'000, Infected: 3'000
struct stats
{
    int people;
    int susceptible;
    int infected;
    int immune;
    int dead;
};

bool update_stats(const struct stats *ptr);
void zero_stat(const struct stats *ptr);
const struct stats *read_stats();
void reset_stats();
// END
