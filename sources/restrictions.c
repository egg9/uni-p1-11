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

void face_mask(void)
{
    stats_t st = *read_stats();

    if (state[0] == inactive)
    {
        st.transmission_rate -= 0.14;
        update_stats(st);
    }
    else
    {
        st.transmission_rate += 0.14;
        update_stats(st);
    }
}

void restrictions(void)
{
    char answer;
    printf("Do you want to implement restrictions? [Y/N] "); //Should be in main
    scanf("%s", &answer);
    if (answer == 'Y' || answer == 'y')
    {
        if (state[0] == inactive)
        {
            printf("Face mask[inactive]? [Y/N] \n");
            char FM;
            scanf("%c", &FM);
            switch (FM)
            {
            case 'Y':
                face_mask();
                printf("Facemasks are now active in the population\n");
                state[0] = state[0] == active ? inactive : active;
                break; // representerer at face masks er active
            default:
                break;
            }
        }
        else
        {
            printf("Face mask[inactive]\n");
        }
    }
    else
    {
        printf("");
    }
}
