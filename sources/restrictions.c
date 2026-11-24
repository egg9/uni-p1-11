#include <ctype.h>
//
// Created by Mads Ulrich Pedersen on 18/11/2026.
//

#include "../headers/restrictions.h"
#include "restrictions.h"

live_e state[3] = {inactive, inactive, inactive};

void set_restrictions(grid_t* town, char answer) {
    if (answer == 'Y' || answer == 'y') {
        printf("Do you want face masks. Will reduce transmission rate by 14 percent [%s]? [Y/N] \n", state[0] == active ? "active" : "inactive");
        char FM;
        do {
            scanf(" %c", &FM);
            while (getchar() != '\n');
            if (toupper(FM) != 'Y' && toupper(FM) != 'N') {
                printf("Invalid input, try again\n");
            }
        } while (toupper(FM) != 'Y' && toupper(FM) != 'N');
        if (toupper(FM) == 'Y') {
            face_mask(town, true);
        } else {
            face_mask(town, false);
        }
    } else {
        return;
    }

    if (answer == 'Y' || answer == 'y') {
        printf("Do you want to close down educational institutions. Will reduce transmission rate by 60 percent [%s]? [Y/N] \n",
               state[1] == active ? "active" : "inactive");
        char EI;
        do {
            scanf(" %c", &EI);
            while (getchar() != '\n');
            if (toupper(EI) != 'Y' && toupper(EI) != 'N') {
                printf("Invalid input, try again\n");
            }
        } while (toupper(EI) != 'Y' && toupper(EI) != 'N');

        if (toupper(EI) == 'Y') {
            educational_institution(town, true);
        } else {
            educational_institution(town, false);
        }
    } else {
        return;
    }

    if (answer == 'Y' || answer == 'y') {
        printf("Do you want to close down public places. Will reduce transmission rate by 70 percent [%s]? [Y/N] \n", state[2] == active ? "active" : "inactive");
        char PB;
        do {
            scanf(" %c", &PB);
            while (getchar() != '\n');
            if (toupper(PB) != 'Y' && toupper(PB) != 'N') {
                printf("Invalid input, try again\n");
            }
        } while (toupper(PB) != 'Y' && toupper(PB) != 'N');
        if (toupper(PB) == 'Y') {
            public_places(town, true);
        } else {
            public_places(town, false);
        }
    } else {
        return;
    }
}


void face_mask(grid_t* town, bool on) {
    if (on && state[0] == active) {
        printf("Face masks are already active\n");
        return;
    }
    if (!on && state[0] == inactive) {
        printf("Face masks are already inactive\n");
        return;
    }

    if (on) {
        town->stats_const.transmission_rate *= 0.86; //reduces transmission rate by 14%
        state[0] = active;
    } else {
        town->stats_const.transmission_rate /= 0.86; //Gets it back to normal
        state[0] = inactive;
    }
}

void educational_institution(grid_t* town, bool on) {
    if (on && state[1] == active) {
        printf("Educational institutions are already active\n");
        return;
    }
    if (!on && state[1] == inactive) {
        printf("Educational institutions are already inactive\n");
        return;
    }

    if (on) {
        town->stats_const.transmission_rate *= 0.40; //will reduce transmission rate by 60%
        state[1] = active;
    } else {
        town->stats_const.transmission_rate /= 0.40;
        state[1] = inactive;
    }
}

void public_places(grid_t* town, bool on) {
    if (on && state[2] == active) {
        printf("Public places are already active\n");
        return;
    }
    if (!on && state[2] == inactive) {
        printf("Public places are already inactive\n");
        return;
    }

    if (on) {
        town->stats_const.transmission_rate *= 0.70; //will reduce transmission rate by 30%
        state[2] = active;
    } else {
        town->stats_const.transmission_rate /= 0.70;
        state[2] = inactive;
    }
}
