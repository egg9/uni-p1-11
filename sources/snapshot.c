#include "snapshot.h"

snapshot_t *initialize_snapshot(grid_t grid)
{

    if (!check_grid(grid))
        return NULL;

    snapshot_t *snapshot_head = calloc(1, sizeof(snapshot_t));
    if (!snapshot_head)
    {
        fprintf(stderr, "Can't reserve enough space for the snapshot struct");
        exit(1);
        return NULL;
    }

    snapshot_head->grid = grid;
    return snapshot_head;
}

bool create_snapshot(snapshot_t **linked_list, grid_t grid)
{
    if (!check_grid(grid) ||
        linked_list == NULL)
        return false;

    snapshot_t *new_snapshot_ptr = calloc(1, sizeof(snapshot_t));
    if (!new_snapshot_ptr)
    {
        fprintf(stderr, "Can't reserve enough space for the snapshot struct");
        exit(1);
        return false;
    }

    // Assinging values to the new snapshot
    new_snapshot_ptr->grid = grid;
    new_snapshot_ptr->prev = *linked_list;

    // Connecting the new snapshot to the linked list
    //! important the linked list will be overriten with the newest snapshot that points to the previous one
    *linked_list = new_snapshot_ptr;

    return true;
}

#define CSV_FILE_PATH_PART_DIR 12
#define CSV_FILE_PATH_PART_EXTENSION 31
bool generate_csv(const snapshot_t *linked_list)
{
    if (linked_list == NULL)
        return false;

    printf("A CSV file will be created with todays date\n");

    time_t now = time(NULL);
    struct tm *t = localtime(&now);

    char file_path[36] = "simulations/\0";
    strftime(file_path + CSV_FILE_PATH_PART_DIR, 20, "%Y-%m-%d_%H-%M-%S", t); // Don't work
    strcat(file_path + CSV_FILE_PATH_PART_EXTENSION, ".csv\0");

    printf("The file can be found at: %s\n", file_path);

    FILE *fptr;
    fptr = fopen(file_path, "w");
    if (!fptr)
    {
        return false;
    }

    const snapshot_t *temp_snapshot_ptr = linked_list;
    fprintf(fptr, "cell, susceptible, infectious, recovered, recovery_rate, transmission_rate, immunity_wane, duration, R_t\n");

    for (int i = 0; temp_snapshot_ptr->prev != NULL; ++i)
    {
        temp_snapshot_ptr = temp_snapshot_ptr->prev;

        for (long long i = 0; i < temp_snapshot_ptr->grid.x_size * temp_snapshot_ptr->grid.y_size; ++i)
        {

            fprintf(fptr, "%lld %d %lf %lf %lf %lf %lf %d %lf\n",
                    i,
                    temp_snapshot_ptr->grid.stats_const.duration,
                    temp_snapshot_ptr->grid.stats[i].infectious,           // totals
                    temp_snapshot_ptr->grid.stats[i].recovered,            // totals
                                                                           //
                    temp_snapshot_ptr->grid.stats_const.recovery_rate,     // =1/duration \gamma
                    temp_snapshot_ptr->grid.stats_const.transmission_rate, // \beta
                    temp_snapshot_ptr->grid.stats_const.immunity_wane,     // how long does immunity last \xi
                                                                           //
                    temp_snapshot_ptr->grid.stats_const.duration,          // const how many days a person is sick
                    temp_snapshot_ptr->grid.stats[i].R_t);
        }
    }
    fclose(fptr);

    return true;
}

bool free_snapshots(snapshot_t *linked_list)
{
    if (linked_list == NULL)
        return false;

    snapshot_t *temp_snapshot_ptr = linked_list;

    while (linked_list->prev != NULL)
    {
        temp_snapshot_ptr = linked_list->prev;
        free(linked_list);
        linked_list = temp_snapshot_ptr;
    }

    return true;
}

bool check_snapshot(snapshot_t linked_list)
{
    if (check_grid(linked_list.grid) && linked_list.prev)
    {
        return true;
    }
    return false;
}