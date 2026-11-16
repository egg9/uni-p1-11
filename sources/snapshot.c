#include "../headers/snapshot.h"

//
// This linked list will point backwards, so the lastest (tail) can be shown first and go towards the oldest (head)
/*
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
*/

// This linked list will point backwards, so the lastest (tail) can be shown first and go towards the oldest (head)
static struct snapshot_t *snapshot_head = NULL;
static struct snapshot_t *snapshot_tail = NULL;
static int lenght = 0;

bool initialize_snapshot()
{
    if (snapshot_head != NULL)
        free(snapshot_head);

    if (snapshot_tail != NULL)
        free(snapshot_tail);

    snapshot_head = calloc(1, sizeof(struct snapshot_t));
    if (!snapshot_head)
    {
        fprintf(stderr, "Can't reserve enough space for the snapshot struct");
        exit(1);
        return false;
    }

    snapshot_tail = snapshot_head;

    return true;
}

bool create_snapshot(stats_t st)
{
    struct snapshot_t *temp_ptr = snapshot_tail;

    snapshot_tail = calloc(1, sizeof(struct snapshot_t));
    if (!snapshot_tail)
    {
        fprintf(stderr, "Can't reserve enough space for the snapshot struct");
        exit(1);
        return false;
    }

    memcpy(snapshot_tail, &st, sizeof(stats_t));
    snapshot_tail->prev = temp_ptr;

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

    struct snapshot_t *temp_ptr = snapshot_tail;
    fprintf(fptr, "susceptible, infectious, recovered, recovery_rate, transmission_rate, immunity_wane, duration, R_t\n");

    for (int i = 0; temp_ptr->prev != 0; ++i)
    {
        temp_ptr = snapshot_tail->prev;

        fprintf(fptr, "%d %d %d %lf %lf %lf %d %lf\n",
                temp_ptr->stats.susceptible,
                temp_ptr->stats.infectious,        // totals
                temp_ptr->stats.recovered,         // totals
                                                   //
                temp_ptr->stats.recovery_rate,     // =1/duration \gamma
                temp_ptr->stats.transmission_rate, // \beta
                temp_ptr->stats.immunity_wane,     // how long does immunity last \xi
                                                   //
                temp_ptr->stats.duration,          // const how many days a person is sick
                temp_ptr->stats.R_t);
    }
    fclose(fptr);

    return true;
}

bool free_snapshots()
{
    struct snapshot_t *temp_ptr = snapshot_tail;

    while (snapshot_tail->prev != 0)
    {
        temp_ptr = snapshot_tail->prev;
        free(snapshot_tail);
        snapshot_tail = temp_ptr;
    }

    if (snapshot_head == snapshot_tail)
        return true;
    else
        return false;
}