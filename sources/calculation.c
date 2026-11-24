#include "../headers/calculations.h"
#include <math.h>

stats_t f(stats_t st, stats_const_t st_const)
{
    double total_population = st.susceptible + st.infectious + st.recovered;

    double gamma = 1.0 / st_const.duration;
    double omega = 1.0 / st_const.immunity_wane;

    double new_infections = (st_const.transmission_rate * st.susceptible * st.infectious) / total_population;
    double new_recoveries = gamma * st.infectious;
    double lost_immunity = omega * st.recovered;

    st.susceptible = -new_infections + lost_immunity;
    st.infectious = new_infections - new_recoveries;

    st.recovered = new_recoveries - lost_immunity;

    return st;
}

stats_t RungeKutta(stats_t st, stats_const_t st_const, double h)
{
    stats_t temp;

    /* k1: hældningen i starten af skridtet */
    stats_t k1 = f(st, st_const);

    /* k2: hældningen halvvejs, estimeret med k1 */
    temp = st;
    temp.susceptible = st.susceptible + h / 2 * k1.susceptible;
    temp.infectious = st.infectious + h / 2 * k1.infectious;
    temp.recovered = st.recovered + h / 2 * k1.recovered;
    stats_t k2 = f(temp, st_const);

    /* k3: hældningen halvvejs, estimeret med k2 */
    temp = st;
    temp.susceptible = st.susceptible + h / 2 * k2.susceptible;
    temp.infectious = st.infectious + h / 2 * k2.infectious;
    temp.recovered = st.recovered + h / 2 * k2.recovered;
    stats_t k3 = f(temp, st_const);

    /* k4: hældningen i slutningen af skridtet, estimeret med k3 */
    temp = st;
    temp.susceptible = st.susceptible + h * k3.susceptible;
    temp.infectious = st.infectious + h * k3.infectious;
    temp.recovered = st.recovered + h * k3.recovered;
    stats_t k4 = f(temp, st_const);

    /* Selve skridtet: vægtet gennemsnit af de fire hældninger */
    st.susceptible += h / 6.0 * (k1.susceptible + 2 * k2.susceptible + 2 * k3.susceptible + k4.susceptible);
    st.infectious += h / 6.0 * (k1.infectious + 2 * k2.infectious + 2 * k3.infectious + k4.infectious);
    st.recovered += h / 6.0 * (k1.recovered + 2 * k2.recovered + 2 * k3.recovered + k4.recovered);

    return st;
}

void CalcNextDay(stats_t *town_stats, stats_const_t st_const)
{

    stats_t st  = *town_stats;
    double N = (st.susceptible + st.infectious + st.recovered);
    // Udregner stats for næste dag
    // Indtil nu er matematikken ikke korrekt – funktionen skal bare kunne tilgå de rigtige variabler uden problemer

    double STEPS_PER_DAY = 15;

    double h = 1.0 / STEPS_PER_DAY;

    /* Integrer én dag frem */
    for (int step = 0; step < STEPS_PER_DAY; step++)
    {
        st = RungeKutta(st, st_const, h);
    }

    st.R_t = (st_const.transmission_rate / (1.0 / st_const.duration)) * (st.susceptible / N); /*Update effective
                                                                                reproductive number*/
    printf("Susceptible: %d   ", (int)st.susceptible);
    printf("Infectious: %d   ", (int)st.infectious); //We cast to int to get rid od the decimal numbers (this only changes copies)
    printf("Recovered: %d\n", (int)st.recovered);

    if (update_stats(town_stats, st) == false)
    { // Gør to ting: opdaterer stats og tjekker for uventede værdier
        printf("ERROR: Unexpected field values!\n");
    }
}