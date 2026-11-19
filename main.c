#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

#include "headers/variables.h"

#include "headers/calculations.h"
#include "headers/input.h"
#include "headers/snapshot.h"
#include "headers/python_call.h"
#include "headers/restrictions.h"

int main(void)
{
    create_stats(InputFirstDay()); // Initial stats are inputted, and the result is fed into stats_t stats to be saved
    initialize_snapshot();
    open_graph();
    printf("Susceptible: %lf\n", read_stats()->susceptible); // Test case that successfully reads the saved value

    // Run each day iteratively. Perhaps call the stepfunction here, so the user can input how many days to skip ahead
    while (true)
    {
        printf("\nHow many days ahead would you skip to?\n");
        int steps = 0;
        scanf(" %d", &steps);

        if (steps < 1)
        {
            break;
        }

        char answer;
        do {
            printf("Do you want to implement restrictions? [Y/N]\n");
            scanf(" %c", &answer);
            while (getchar() != '\n');      // throw away the rest of the line
            answer = toupper(answer);       // 'y' -> 'Y', 'n' -> 'N'
        } while (answer != 'Y' && answer != 'N');
        restrictions(answer);

        for (int step = 0; step < steps; step++)
        {
            CalcNextDay(*read_stats());
            create_snapshot(*read_stats());
            append_day_graph(*read_stats());
        }
    }
    close_graph();

    printf("%d", generate_csv());

    return 0;
}