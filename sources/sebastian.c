#include "../headers/sebastian.h"

stats_t InputFirstDay()
{ // Løsning med returtype struct, overvej void hvis stats_t kan være global og static
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
    scanf(" %d", &day_one_stats.susceptible);
    scanf(" %lf", &day_one_stats.recovery_rate);
    scanf(" %lf", &day_one_stats.transmission_rate);
    scanf(" %lf", &day_one_stats.immunity_wane);
    scanf(" %d", &day_one_stats.duration);

    return day_one_stats; // Returnér den nye struct
}

void CalcNextDay(stats_t st)
{
    // Udregner stats for næste dag
    // Indtil nu er matematikken ikke korrekt – funktionen skal bare kunne tilgå de rigtige variabler uden problemer

    if (st.susceptible < 20)
    {
        st.susceptible *= 2;
    }
    else
    {
        st.susceptible /= 2;
    }

    if (update_stats(st) == false)
    { // Gør to ting: opdaterer stats og tjekker for uventede værdier
        printf("ERROR: Unexpected field values!\n");
    }
}

/* // Gammel version, anden metode benyttes i main
void RunSimulation() {
    // Brugeren inputter hvor mange dage fremad simulationen skal køre
    //
    printf("How many days ahead would you skip to?\n");
    int i = 0;
    scanf("%d", &i);

    while (i > 0) {
        CalcNextDay(*read_stats());
        // I
        i--;
    }

    do {
        CalcNextDay(*read_stats());
        i--;
    } while (i > 0);
}*/