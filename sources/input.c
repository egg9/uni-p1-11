#include "../headers/input.h"

stats_t InputFirstDay()
{ // Løsning med returtype struct, overvej void hvis stats_t kan være global og static
    // Tekst der introducerer programmet (evt. bare have det i main)
    printf("Input values for the following variables in the corresponding order:\n");
    printf(" Susceptible (int)\n"
           " Transmission rate (double)\n"
           " Immunity wane (double)\n"
           " Duration (int)\n");

    // Lav en ny tom struct
    stats_t day_one_stats = {};

    // Input nye værdier på felterne
    scanf(" %d", &day_one_stats.susceptible);
    scanf(" %lf", &day_one_stats.transmission_rate);
    scanf(" %lf", &day_one_stats.immunity_wane);
    scanf(" %d", &day_one_stats.duration);

    return day_one_stats; // Returnér den nye struct
}