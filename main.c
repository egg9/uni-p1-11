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
static void skip_days(void);
static int check_int(const char *prompt);
static void clear_input_line(void);

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
            skip_days();
            break;

        case MENU_ADD_RESTRICTION:
            set_restrictions('Y');
            break;

        case MENU_SELECT_CELL:
            printf("Selecting a cell in the grid is not implemented yet\n");
            break;

        case MENU_SAVE_CSV:
            if (!generate_csv())
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

static void print_menu(void)
{
    printf("\n----- Menu -----\n");
    printf("%d. Skip ahead a number of days\n", MENU_SKIP_DAYS);
    printf("%d. Add a restriction\n", MENU_ADD_RESTRICTION);
    printf("%d. Select a cell in the grid (x, y) [not implemented]\n", MENU_SELECT_CELL);
    printf("%d. Save CSV file\n", MENU_SAVE_CSV);
    printf("%d. Exit\n", MENU_EXIT);
}

static void skip_days(void)
{
    int days = check_int("How many days ahead do you want to skip? ");
    if (days < 1)
    {
        printf("The number of days must be at least 1\n");
        return;
    }

    for (int day = 0; day < days; day++)
    {
        CalcNextDay(*read_stats());
        create_snapshot(*read_stats());
        append_day_graph(*read_stats());
    }
    printf("Transmission rate: %lf\n", read_stats()->transmission_rate);
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
