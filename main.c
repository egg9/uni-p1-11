#include <stdio.h>
#include <stdbool.h>

#include "headers/colors.h"
#include "headers/variables.h"

#include "headers/hassan.h"
#include "headers/mads.h"
#include "headers/magnus.h"
#include "headers/max.h"
#include "headers/sebastian.h"
#include "headers/tobias.h"

int main(void)
{
    printf(RED "Hello World!" reset);
    create_stats(InputFirstDay()); // Initial stats are inputted, and the result is fed into stats_t stats to be saved
    printf("Susceptible: %d\n", read_stats()->susceptible); // Test case that successfully reads the saved value

    // Run each day iteratively. Perhaps call the stepfunction here, so the user can input how many days to skip ahead

    //CalcNextDay(*read_stats()); // Pointer fixed it. Somehow.
    //printf("Susceptible: %d\n", read_stats()->susceptible); // Same testing case, can safely be deleted

    return 0;
}
