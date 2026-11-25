#include <stdio.h>
#include <stdbool.h>

#include "variables.h"

#include "calculations.h"
#include "input.h"
#include "snapshot.h"
#include "python_call.h"
#include "restrictions.h"

enum menu_option
{
    MENU_SKIP_DAYS = 1,
    MENU_ADD_RESTRICTION = 2,
    MENU_SELECT_CELL = 3,
    MENU_SAVE_CSV = 4,
    MENU_EXIT = 5
};

static void print_menu(void);
static void skip_days(snapshot_t *snapshot, const grid_t *town);
static int check_int(const char *prompt);
static void clear_input_line(void);

int main(void)
{
    // Initial stats are inputted, and the result is fed into stats_t stats to be saved
    grid_t *town;
    {
        // The loop to get input
        while ((town = create_grid(input_grid_size(false), input_grid_size(true))) == NULL)
        {
            printf("illagal input, try again\n");
        }

        // Initial stats are inputted, and the result is fed into stats_t stats to be saved
        stats_t town_stats = {0};
        stats_const_t town_stats_const = {0};

        while (InputFirstDay(&town_stats, &town_stats_const) == false) // TODO: check for error
        {
            printf("illagal input, try again\n");
        }

        initialize_grid(town, town_stats, town_stats_const);
    }

    snapshot_t *town_snapshots;
    while ((town_snapshots = initialize_snapshot(*town)) == NULL)
    {
        printf("Something with snapshots went wrong, trying again\n");
    }

    open_graph();
    // printf("Susceptible: %lf\n", read_stats()->susceptible); // Test case that successfully reads the saved value

    bool running = true;
    while (running)
    {
        print_menu();
        int choice = check_int("Choose an option: ");
        if (choice == -1)
        {
            choice = MENU_EXIT;
        }

        switch (choice)
        {
        case MENU_SKIP_DAYS:
            skip_days(town_snapshots, town);
            break;

        case MENU_ADD_RESTRICTION:
            set_restrictions(town, 'Y');
            break;

        case MENU_SELECT_CELL:
            printf("Selecting a cell in the grid is not implemented yet\n");
            break;

        case MENU_SAVE_CSV:
            if (!generate_csv(town_snapshots))
            {
                printf("Could not save the CSV file\n");
            }
            break;

        case MENU_EXIT:
            running = false;
            break;

        default:
            printf("Unknown option, choose a number from %d to %d\n", MENU_SKIP_DAYS, MENU_EXIT);
            break;
        }
    }
    return 0;
}

static void print_menu(void)
{
    printf("\n----- Menu -----\n");
    printf("%d. Skip ahead a number of days\n", MENU_SKIP_DAYS);
    printf("%d. Add a restriction\n", MENU_ADD_RESTRICTION);
    printf("%d. Select a cell in the grid (x, y) [not implemented]\n", MENU_SELECT_CELL);
    printf("%d. Save CSV file\n", MENU_SAVE_CSV);
    printf("%d. Exit\n", MENU_EXIT);
}

static void skip_days(snapshot_t *snapshot, const grid_t *town)
{
    int days = check_int("How many days ahead do you want to skip? ");
    if (days < 1)
    {
        printf("The number of days must be at least 1\n");
        return;
    }

    for (int day = 0; day < days; day++)
    {
        for (long long index = 0; index < town->x_size * town->y_size; ++index)
        {
            CalcNextDay(&town->stats[index], town->stats_const);
            append_day_graph(town->stats[index], town->stats_const);
        }
        create_snapshot(snapshot, *town);
        printf("Transmission rate: %lf\n", town->stats_const.transmission_rate);


        double total_susceptible = 0;
        double total_infectious = 0;
        double total_recovered = 0;
        for (long long index = 0; index < town->x_size * town->y_size; ++index)
        {
            total_susceptible += town->stats[index].susceptible;
            total_infectious += town->stats[index].infectious;
            total_recovered += town->stats[index].recovered;
        }
        printf("susceptible: %d\n", (int)total_susceptible);
        printf("infectious: %d\n", (int)total_infectious);
        printf("recovered: %d\n", (int)total_recovered);
        printf("total population: %d\n", (int)(total_susceptible + total_infectious + total_recovered));
    }
}

static int check_int(const char *prompt)
{
    int input;
    while (true)
    {
        printf("%s", prompt);
        int result = scanf(" %d", &input);
        if (result == 1)
        {
            clear_input_line();
            return input;
        }
        if (result == EOF)
        {
            return -1;
        }
        printf("Invalid input, please type a whole number\n");
        clear_input_line();
    }
}

static void clear_input_line(void)
{
    int input;
    while ((input = getchar()) != '\n' && input != EOF);
}
