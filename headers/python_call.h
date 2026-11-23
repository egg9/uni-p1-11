#ifndef PYTHON_CALL_H
#define PYTHON_CALL_H

#include <stdio.h>
#include <stdlib.h>

#include "../headers/variables.h"


void open_graph();

void append_day_graph(stats_t st);

bool close_graph();

#endif