#include "../headers/snapshot.h"

//
// This linked list will point backwards, so the lastest (tail) can be shown first and go towards the oldest (head)
static stats_t *snapshots = NULL;
static int lenght = 0;
static int capacity = 0;

bool initialize_snapshot()
{
    if (snapshots != NULL)
        free(snapshots);

    lenght = 0;
    capacity = 0;
    snapshots = calloc(365, sizeof(stats_t));
    if (!snapshots)
    {
        fprintf(stderr, "Can't reserve enough space for the snapshot");
        exit(1);
        return false;
    }

    return true;
}

bool create_snapshot(stats_t st)
{
    if (lenght >= capacity)
    {
        stats_t *tmp = realloc(snapshots, capacity * sizeof(stats_t) + 365);
        if (!tmp)
        {
            fprintf(stderr, "Can't reserve enough space for a new snapshot");
            exit(1);
            return false;
        }

        snapshots = tmp;
        capacity += 365;
    }

    snapshots[lenght] = st;
    lenght++;

    return true;
}

bool generate_csv(char *path)
{
    FILE *fptr;
    fptr = fopen(path, "w");
    if (!fptr)
    {
        return false;
    }

    fprintf(fptr, "day, susceptible, infectious, recovered, recovery_rate, transmission_rate, immunity_wane, duration, R_t\n");

    for (int i = 0; i < lenght; ++i)
    {

        fprintf(fptr, "%lf %lf %lf %lf %lf %lf %d %lf",
                snapshots[i].susceptible,
                snapshots[i].infectious,        // totals
                snapshots[i].recovered,         // totals
                                                //
                snapshots[i].recovery_rate,     // =1/duration \gamma
                snapshots[i].transmission_rate, // \beta
                snapshots[i].immunity_wane,     // how long does immunity last \xi
                                                //
                snapshots[i].duration,          // const how many days a person is sick
                snapshots[i].R_t);
    }
    fclose(fptr);
}

const stats_t * const read_snapshots() {
    return snapshots;
}

bool free_snapshots()
{
    if (snapshots != NULL)
    {
        free(snapshots);
        return true;
    }

    return false;
}