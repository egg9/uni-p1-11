#include "../headers/sebastian.h"
#include <stdio.h> // Fjern i fremtiden fordi main.c alligevel har dette library inkluderet
#include "variables.h" // Overvej om denne også skal fjernes hvis main alligevel har dette library

void InputFirstDay() {
    // Tekst der introducerer programmet (evt. bare have det i main)


    // Lav en ny struct
    struct stats_t first_day_stats = {};

    // Input nye værdier på felterne, hovedsageligt susceptible på felt 0
    scanf(" %d", &first_day_stats.susceptible);

    struct stats_t; // structen
}