#include "../headers/calculations.h"



void CalcNextDay(stats_t st)
{
    int N = (st.susceptible + st.infectious + st.recovered);
    // Udregner stats for næste dag
    // Indtil nu er matematikken ikke korrekt – funktionen skal bare kunne tilgå de rigtige variabler uden problemer

    st.susceptible = st.susceptible - (st.transmission_rate * st.susceptible //Update susceptible
        * st.infectious)/N + st.immunity_wane * st.recovered;

    st.infectious = st.infectious + (st.transmission_rate * st.susceptible //Update infectious
        * st.infectious)/N - (1/st.duration) * st.infectious;

    st.recovered = st.recovered + ((1/st.duration) * st.infectious) - //Update recovered
        (st.immunity_wane * st.recovered);

    st.R_t = (st.transmission_rate / (1/st.duration)) * (st.susceptible / N); /*Update effective
                                                                              reproductive number*/

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

double f(double x, double y) {
    return y;
}


double RungeKutta(double x_0, double y_0, double x_end, double h) {

    double x = x_0;
    double y = y_0;



    while (x < x_end) {
        double k1 = h * f(x, y);
        double k2 = h * f(x + h / 2, y + k1 / 2);
        double k3 = h * f(x + h / 2, y + k2 / 2);
        double k4 = h * f(x + h, y + k3);

        y += (k1 + 2*k2 + 2*k3 + k4) / 6;
        x += h;
    }

    return y;

}