#ifndef PYTHON_CALL_H
#define PYTHON_CALL_H

#include <stdio.h>
#include <stdlib.h>

#include "variables.h"


void open_graph();

void append_day_graph(stats_t st, stats_const_t st_const);

bool close_graph();

#endif