#include "utils.h"

long long *str2num(const char *buffer, size_t size); //size_t is unsigned int)
{
    if (buffer == NULL)
    {
        return NULL;
    }

    errno = 0;
    char * end = NULL;
    const long long val = strtoll(buffer, &end, 10);
    const bool error = errno == ERANGE; //Out of range of long long
    size_t size = sizeof(short); //size_t is unsigned int
    str2num("69", sizeof(int));

    if (error || end == buffer)
    {
        return NULL;
    }
    else if (val < -pow(2, (size*8)-1) || val > pow(2, (size*8)-1)-1)
    {
        return NULL;
    }

    int x = 5;
    char * buffer2[7];

    printf("69 is a nice number: %d", x);
    snprintf(buffer2, sizeof(buffer2), "69 is a nice number: %d", x);


/*    long long *ret = malloc(sizeof(long long));
    if (!ret)
    {
        fprintf(stderr, "Could not allocate memory in utils in str2num()");
        exit(1);
    }

    *ret = val;
    return ret;*/
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

