#include "../headers/calculations.h"



void CalcNextDay(stats_t st)
{
    int N = (st.susceptible + st.infectious + st.recovered);
    // Udregner stats for næste dag
    // Indtil nu er matematikken ikke korrekt – funktionen skal bare kunne tilgå de rigtige variabler uden problemer

    st.susceptible = st.susceptible - (st.transmission_rate * st.susceptible
        * st.infectious)/N + st.immunity_wane * st.recovered;
    st.infectious = st.infectious + (st.transmission_rate * st.susceptible
        * st.infectious)/N - (1/st.duration) * st.infectious;
    st.recovered = st.recovered + ((1/st.duration) * st.infectious) -
        (st.immunity_wane * st.recovered);

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