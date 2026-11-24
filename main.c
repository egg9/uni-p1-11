#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

#include "variables.h"

#include "calculations.h"
#include "input.h"
#include "snapshot.h"
#include "python_call.h"
#include "restrictions.h"

int main(void)
{
    // Initial stats are inputted, and the result is fed into stats_t stats to be saved
    grid_t *town;
    {
        // Initial stats are inputted, and the result is fed into stats_t stats to be saved
        stats_t *town_stats;
        while ((town_stats = create_stats(InputFirstDay())) == NULL)
        {
            printf("illagal input, try again\n");
        }

        // The loop to get input
        while ((town = create_grid(input_grid_size(false), input_grid_size(true))) == NULL)
        {
            printf("illagal input, try again\n");
        }
    }

    snapshot_t *town_snapshots;
    while ((town_snapshots = initialize_snapshot(*town)) == NULL)
    {
        printf("Something with snapshots went wrong, trying again\n");
    }

    open_graph();
    // printf("Susceptible: %lf\n", read_stats()->susceptible); // Test case that successfully reads the saved value

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
        do
        {
            printf("Do you want to change restrictions? [Y/N]\n");
            scanf(" %c", &answer);
            while (getchar() != '\n');   // throw away the rest of the line
            answer = toupper(answer);    // 'y' -> 'Y', 'n' -> 'N'
        } while (answer != 'Y' && answer != 'N');
        set_restrictions(town, answer);

        for (long long index = 0; index < town->x_size * town->y_size; ++index)
        {
            for (int step = 0; step < steps; step++)
            {
                CalcNextDay(&town->stats[index], town->stats_const);

                //append_day_graph(town->stats[i]); //needs more work
            }
            printf("Transmission rate: %lf", town->stats_const.transmission_rate);
        }
        create_snapshot(town_snapshots, *town);
    }
    close_graph();

    printf("%d", generate_csv(town_snapshots));

    return 0;
}