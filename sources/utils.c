#include "utils.h"

// size_t is unsigned int)
long long str2ll(const char *buffer, bool *error)
{
    if (buffer == NULL)
    {
        *error = true;
        return 0;
    }

    errno = 0;
    char *end = NULL;
    const long long val = strtoll(buffer, &end, 10);
    *error = (errno == ERANGE); // Out of range of long long

    if (*error || end == buffer)
    {
        *error = true;
        return 0;
    }

    *error = false;
    return val;
}

long str2long(const char *buffer, bool *error)
{
    const long long val = str2ll(buffer, error);

    if (val < LONG_MIN || val > LONG_MAX)
    {
        *error = true;
        return 0;
    }

    *error = false;
    return val;
}

int str2int(const char *buffer, bool *error)
{
    const long long val = str2ll(buffer, error);

    if (val < INT_MIN || val > INT_MAX)
    {
        *error = true;
        return 0;
    }

    *error = false;
    return val;
}

short str2short(const char *buffer, bool *error)
{
    const long long val = str2ll(buffer, error);

    if (val < SHRT_MIN || val > SHRT_MAX)
    {
        *error = true;
        return 0;
    }

    *error = false;
    return val;
}

char str2char(const char *buffer, bool *error)
{
    const long long val = str2ll(buffer, error);

    if (val < CHAR_MIN || val > CHAR_MAX)
    {
        *error = true;
        return 0;
    }

    *error = false;
    return val;
}

double str2double(const char *buffer, bool *error)
{
    if (buffer == NULL)
    {
        *error = true;
        return 0;
    }

    errno = 0;
    char *end = NULL;
    const double val = strtod(buffer, &end);
    *error = (errno == ERANGE);

    if (error || end == buffer)
    {
        *error = true;
        return 0;
    }

    *error = false;
    return val;
}
