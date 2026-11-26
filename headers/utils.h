#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <limits.h>
#include <math.h>

/**
 * @param
 * buffer, a string buffer containing a number and a terminator
 * error, is a out parameter to say if the operation was succesful
 * @return 
 * A value of the wanted number.
 */
long long str2ll(const char *buffer, bool *error);
long str2long(const char *buffer, bool *error);
int str2int(const char *buffer, bool *error);
short str2short(const char *buffer, bool *error);
char str2char(const char *buffer, bool *error);
double str2double(const char* buffer, bool *error);

