#include "../headers/snapshot.h"

// This linked list will point backwards, so the lastest (tail) can be shown first and go towards the oldest (head)
static struct snapshot_t *snapshot_head = NULL;
static struct snapshot_t *snapshot_tail = NULL;

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
}

bool generate_csv(char *path, char *filename);
void print_graph(int size);

void free_snapshots()
{
    struct snapshot_t *temp_ptr = snapshot_tail;

    while (snapshot_tail->prev != 0)
    {
        temp_ptr = snapshot_tail->prev;
        free(snapshot_tail);
        snapshot_tail = temp_ptr;
    }
}