#include "utils.h"

long long *str2num(const char *buffer, long long int max, long long int min)
{
    if (buffer == NULL)
    {
        return NULL;
    }

    errno = 0;
    char * end = NULL;
    const long long val = strtoll(buffer, &end, 10);
    const bool error = errno == ERANGE;

    if (error || end == buffer)
    {
        return NULL;
    }
    else if (val < min || val > max)
    {
        return NULL;
    }

    long long *ret = malloc(sizeof(long long));
    if (!ret)
    {
        fprintf(stderr, "Could not allocate memory in utils in str2num()");
        exit(1);
    }

    *ret = val;
    return ret;
}

double * str2double(const char* buffer, double max, double min)
{
    if (buffer == NULL)
    {
        return NULL;
    }

    errno = 0;
    char * end = NULL;
    const double val = strtod(buffer, &end);
    const bool error = errno == ERANGE;

    if (error || end == buffer)
    {
        return NULL;
    }
    else if (val < min || val > max)
    {
        return NULL;
    }

    double *ret = malloc(sizeof(double));
    if (!ret)
    {
        fprintf(stderr, "Could not allocate memory in utils in str2num()");
        exit(1);
    }

    *ret = val;
    return ret;
}