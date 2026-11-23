#ifndef PROJECT1_RESTRICTIONS_H
#define PROJECT1_RESTRICTIONS_H

#include <stdbool.h>
#include <stdio.h>

typedef enum live
{
    active,
    inactive
} live_e;
void set_restrictions(char answer);
void face_mask(bool on);
void educational_institution(bool on);
void public_places(bool on);



#endif //PROJECT1_RESTRICTIONS_H
