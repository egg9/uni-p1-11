#include <ctype.h>
//
// Created by Mads Ulrich Pedersen on 18/11/2026.
//
typedef enum live
{
    active,
    inactive
} live_e;
live_e state[5] = {inactive, inactive, inactive, inactive, inactive};

#include "../headers/restrictions.h"
#include "variables.h"

void face_mask(bool on)
{
    if (on && state[0] == active) {
        printf("Face masks are already active");
        return;
    }
    if (!on && state[0] == inactive) {
        printf("Face masks are already inactive");
        return;
    }

    stats_t st = *read_stats();

    if (on)
    {
        st.transmission_rate -= 0.14;
    }
    else
    {
        st.transmission_rate += 0.14;
    }
    update_stats(st);
}

void restrictions(char answer)
{
    if (answer == 'Y' || answer == 'y')
    {
        if (state[0] == inactive)
        {
            printf("Do you want face masks[%s]? [Y/N] \n", state[0] == active ? "active" : "inactive");
            char FM;
            scanf(" %c", &FM);
            if (toupper(FM) == 'Y') {
                face_mask(true);
            } else {
                face_mask(false);
            }
        }
    }
    else
    {
        printf("");
    }
}
