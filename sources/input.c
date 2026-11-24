#include "../headers/input.h"

bool InputFirstDay(stats_t *day_one_stats, stats_const_t *day_one_stats_const)
{ // Løsning med returtype struct, overvej void hvis stats_t kan være global og static
    // Tekst der introducerer programmet (evt. bare have det i main)
    // Lav en ny tom struct
    /*stats_t day_one_stats = (stats_t){};
    stats_const_t day_one_stats_const = (stats_const_t){};*/

    // Input nye værdier på felterne
    printf("Input the value for the size of the susceptible group: \n");
    scanf(" %lf", &day_one_stats->susceptible);

    printf("\nInput the value of the transmission rate as a decimal number: \n");
    scanf(" %lf", &day_one_stats_const->transmission_rate);

    printf("\nInput the value for the immunity waning time as a whole number \n");
    scanf(" %lf", &day_one_stats_const->immunity_wane);

    printf("\nInput the value for the duration of the disease in whole days: \n");
    scanf(" %d", &day_one_stats_const->duration);

    printf("\nInput the amount of starting infectious: \n");
    scanf(" %lf", &day_one_stats->infectious);

    if (day_one_stats->infectious < 0)
    {
        printf("infectious cant be less then 0, infectious set to 1");
        day_one_stats->infectious = 1;
    }

    printf("\nThe basic reproduction number is: %lf\n",
           day_one_stats_const->transmission_rate / (1.0 / day_one_stats_const->duration));

    return true; // Returnér den nye struct
}

int input_grid_size(bool x_or_y)
{
    int inp = 0;

    if (x_or_y)
    {
        printf("How wide should the city be: ");
    }
    else
    {
        printf("How high should the city be: ");
    }

    scanf("%d", &inp);
    return inp;
}