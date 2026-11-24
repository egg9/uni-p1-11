#include "snapshot.h"

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

snapshot_t *initialize_snapshot(grid_t grid)
{

    if (check_grid(grid))
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

bool create_snapshot(snapshot_t *linked_list, grid_t grid)
{
    if (check_grid(grid) || linked_list == NULL)
        return false;

    snapshot_t *temp_ptr = calloc(1, sizeof(snapshot_t));
    if (!temp_ptr)
    {
        fprintf(stderr, "Can't reserve enough space for the snapshot struct");
        exit(1);
        return false;
    }

    temp_ptr->grid = grid;
    temp_ptr->prev = linked_list;
    linked_list = temp_ptr;

    return true;
}

#define CSV_FILE_PATH_PART_DIR 12
#define CSV_FILE_PATH_PART_EXTENSION 31
bool generate_csv(snapshot_t *linked_list)
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

    /* Needs fixing if implemented
    while (true)
    {
        printf("Chose up to 19 characters long name for the new CSV file [a-zA-Z0-9]: ");
        char file_dir[] = "simulations/\0";
        char file_name[20] = {0};
        char file_extension[] = ".csv\0";

        char ch = 0;
        fflush(stdin);
        for (int i = 0; i < 19; ++i)
        {
            if ((ch = getchar()) == '\n')
            {
                if (i == 0)
                {
                    time_t now = time(NULL);
                    tm *t = localtime(&now);

                    strftime(file_name, sizeof(file_name), "%d-%m-%Y %H:%M:%S\0", t);
                }
                else
                {
                    file_name[i + 1] = '\0';
                }
                break;
            }

            file_name[i] = (isalnum(ch)) ? ch : --i; // overrides file_name[i] with 'ch' if 'ch' is alphanumeric if not it will decrement 'i'
            // Usage of decrement 'i' is allowed, because the operation returns a value
        }
        fflush(stdin);

        char *illigal_names[] = {"CON", "PRN", "AUX", "NUL", "COM1", "COM2", "COM3", "COM4", "COM5", "COM6", "COM7", "COM8", "COM9", "LPT1", "LPT2", "LPT3", "LPT4", "LPT5", "LPT6", "LPT7", "LPT8", "LPT9"};
        if (strlen(file_name) == 3 || strlen(file_name) == 4)
        {
            for (int i = 0; i > sizeof(illigal_names); ++i)
            {
                if (strcmp(file_name, illigal_names[i]) != 0)
                {
                    printf("File name is violating the windows name convention\n");
                    goto CSV;
                }
            }
        }
    }

    char file_path[33] = {0};
    strcat(file_path, file_dir);
    strcat(file_path + 12, file_name);
    strcat(file_path + strlen(file_name), file_extension);*/

    FILE *fptr;
    fptr = fopen(file_path, "w");
    if (!fptr)
    {
        return false;
    }

    snapshot_t *temp_ptr = linked_list;
    fprintf(fptr, "cell, susceptible, infectious, recovered, recovery_rate, transmission_rate, immunity_wane, duration, R_t\n");

    for (int i = 0; temp_ptr->prev != NULL; ++i)
    {
        temp_ptr = temp_ptr->prev;

        for (long long i = 0; i < temp_ptr->grid.x_size * temp_ptr->grid.y_size; ++i)
        {

            fprintf(fptr, "%lld %d %lf %lf %lf %lf %lf %d %lf\n",
                    i,
                    temp_ptr->grid.stats_const.duration,
                    temp_ptr->grid.stats[i].infectious,        // totals
                    temp_ptr->grid.stats[i].recovered,         // totals
                                                       //
                    temp_ptr->grid.stats_const.recovery_rate,     // =1/duration \gamma
                    temp_ptr->grid.stats_const.transmission_rate, // \beta
                    temp_ptr->grid.stats_const.immunity_wane,     // how long does immunity last \xi
                                                       //
                    temp_ptr->grid.stats_const.duration,          // const how many days a person is sick
                    temp_ptr->grid.stats[i].R_t);
        }
    }
    fclose(fptr);

    return true;
}

bool free_snapshots(snapshot_t *linked_list)
{
    if (linked_list == NULL)
        return false;

    snapshot_t *temp_ptr = linked_list;

    while (linked_list->prev != NULL)
    {
        temp_ptr = linked_list->prev;
        free(linked_list);
        linked_list = temp_ptr;
    }

    return true;
}

bool check_snapshot(snapshot_t linked_list) {
    if (check_grid(linked_list.grid) && linked_list.prev) {
        return true;
    } 
    return false;
}