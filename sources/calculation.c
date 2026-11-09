#include "../headers/calculations.h"

stats_t f(stats_t st) {
    double total_population = st.susceptible + st.infectious + st.recovered;
    double gamma = 1.0 / st.duration;

    double new_infections = st.transmission_rate * st.susceptible * st.infectious / total_population;
    double new_recoveries = gamma * st.infectious;
    double lost_immunity  = st.immunity_wane * st.recovered;

    st.susceptible = -new_infections + lost_immunity;
    st.infectious  =  new_infections - new_recoveries;
    st.recovered   =  new_recoveries - lost_immunity;

    return st;

}

stats_t RungeKutta(stats_t st, double h) {
    stats_t temp;

    /* k1: hældningen i starten af skridtet */
    stats_t k1 = f(st);

    /* k2: hældningen halvvejs, estimeret med k1 */
    temp = st;
    temp.susceptible = st.susceptible + h / 2 * k1.susceptible;
    temp.infectious  = st.infectious  + h / 2 * k1.infectious;
    temp.recovered   = st.recovered   + h / 2 * k1.recovered;
    stats_t k2 = f(temp);

    /* k3: hældningen halvvejs, estimeret med k2 */
    temp = st;
    temp.susceptible = st.susceptible + h / 2 * k2.susceptible;
    temp.infectious  = st.infectious  + h / 2 * k2.infectious;
    temp.recovered   = st.recovered   + h / 2 * k2.recovered;
    stats_t k3 = f(temp);

    /* k4: hældningen i slutningen af skridtet, estimeret med k3 */
    temp = st;
    temp.susceptible = st.susceptible + h * k3.susceptible;
    temp.infectious  = st.infectious  + h * k3.infectious;
    temp.recovered   = st.recovered   + h * k3.recovered;
    stats_t k4 = f(temp);

    /* Selve skridtet: vægtet gennemsnit af de fire hældninger */
    st.susceptible += h / 6.0 * (k1.susceptible + 2 * k2.susceptible + 2 * k3.susceptible + k4.susceptible);
    st.infectious  += h / 6.0 * (k1.infectious  + 2 * k2.infectious  + 2 * k3.infectious  + k4.infectious);
    st.recovered   += h / 6.0 * (k1.recovered   + 2 * k2.recovered   + 2 * k3.recovered   + k4.recovered);

    return st;
}

void CalcNextDay(stats_t st)
{
    int N = (st.susceptible + st.infectious + st.recovered);
    // Udregner stats for næste dag
    // Indtil nu er matematikken ikke korrekt – funktionen skal bare kunne tilgå de rigtige variabler uden problemer

    double STEPS_PER_DAY = 15;

    double h = 1.0 / STEPS_PER_DAY;

    /* Integrer én dag frem */
    for (int step = 0; step < STEPS_PER_DAY; step++) {
        RungeKutta(st, h);
    }

    st.R_t = (st.transmission_rate / (1.0/st.duration)) * (st.susceptible / N); /*Update effective
                                                                              reproductive number*/

    if (update_stats(st) == false)
    { // Gør to ting: opdaterer stats og tjekker for uventede værdier
        printf("ERROR: Unexpected field values!\n");
    }
}