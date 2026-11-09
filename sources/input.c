#include "../headers/input.h"

stats_t InputFirstDay()
{ // Løsning med returtype struct, overvej void hvis stats_t kan være global og static
    // Tekst der introducerer programmet (evt. bare have det i main)
    // Lav en ny tom struct
    stats_t day_one_stats = (stats_t){};

    // Input nye værdier på felterne
    printf("Input the value for the size of the susceptible group: \n");
    scanf(" %lf", &day_one_stats.susceptible);

    printf("\nInput the value of the transmission rate as a decimal number: \n");
    scanf(" %lf", &day_one_stats.transmission_rate);

    printf("\nInput the value for the immunity waning time as a whole number \n");
    scanf(" %lf", &day_one_stats.immunity_wane);

    printf("\nInput the value for the duration of the disease in whole days: \n");
    scanf(" %d", &day_one_stats.duration);

    printf("\nInput the amount of starting infectious: \n");
    scanf(" %lf", &day_one_stats.infectious);

    if (&day_one_stats.infectious < 0) {
        printf("infectious cant be less then 0, infectious set to 1");
        day_one_stats.infectious = 1;
    }

    printf("\nThe basic reproduction number is: %lf\n",
        day_one_stats.transmission_rate/(1.0/day_one_stats.duration));

    return day_one_stats; // Returnér den nye struct
}