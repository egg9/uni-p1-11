#ifndef PROJECT1_RESTRICTIONS_H
#define PROJECT1_RESTRICTIONS_H

#include <stdbool.h>
#include <stdio.h>
#include "variables.h"
#include "grid.h"

typedef enum live
{
    active,
    inactive
} live_e;
void set_restrictions(grid_t* town, char answer);
void face_mask(grid_t* town, bool on);
void educational_institution(grid_t* town, bool on);
void public_places(grid_t* town, bool on);



#endif //PROJECT1_RESTRICTIONS_H
