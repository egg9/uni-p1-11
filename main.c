#include <stdio.h>
#include <stdbool.h>

#include "headers/variables.h"

#include "headers/calculations.h"
#include "headers/input.h"
#include "headers/snapshot.h"
#include "headers/python_call.h"
#include "headers/restrictions.h"

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
    create_stats(InputFirstDay());
    initialize_snapshot();
    open_graph();
    printf("Susceptible: %lf\n", read_stats()->susceptible);

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
    }
    close_graph();

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
