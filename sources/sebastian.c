#include "../headers/sebastian.h"
#include <stdio.h> // Fjern i fremtiden fordi main.c alligevel har dette library inkluderet
#include "../headers/variables.h" // Overvej om denne også skal fjernes hvis main alligevel har dette library

stats_t InputFirstDay() { // Løsning med returtype struct, overvej void hvis stats_t kan være global og static
    // Tekst der introducerer programmet (evt. bare have det i main)
    printf("Input values for the following variables in the corresponding order:\n");
    printf(" Susceptible (int)\n"
           " Recovery rate (double)\n"
           " Transmission rate (double)\n"
           " Immunity wane (double)\n"
           " Duration (int)\n");

    // Lav en ny tom struct
    stats_t day_one_stats = {};

    // Input nye værdier på felterne
    scanf("%d, %lf, %lf, %lf, %d",
        &day_one_stats.susceptible,
        &day_one_stats.recovery_rate,
        &day_one_stats.transmission_rate,
        &day_one_stats.immunity_wane,
        &day_one_stats.duration);

    return day_one_stats; // Returnér den nye struct
}