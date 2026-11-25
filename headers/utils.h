#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <limits.h>
#include <math.h>

/**
 * @param
 * buffer, a string buffer containing a number and a terminator
 * max, what is maximum number should be possible to return
 * min, what is minimum number should be possible to return
 * @return 
 * A pointer to the wanted number.
 * If there was an error the pointer would be null, otherwise remember to free.
 */
long long * str2int64(const char* buffer, long long int max, long long int min);

double * str2double(const char* buffer, double max, double min);

