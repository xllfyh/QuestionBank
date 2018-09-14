#include <stdio.h>
#include <stdlib.h>

#include "llist.h"
#include "queue.h"

QUEUE *queue_create(int size)
{
    LLIST *queue;
    queue = llist_create(size);
    return queue;
}

int queue_en(QUEUE *qu, const void *data)
{
    LLIST *queue = qu;
    return llist_insert(queue, data, LLIST_BACKWARD);
}

static int always_match(const void *data, const void *key)
{
    return 0;
}

int queue_de(QUEUE *qu, void *data)
{
    LLIST *queue = qu;
    return llist_fetch(queue, (void *)0, always_match, data);
}

void queue_destroy(QUEUE *qu)
{
    LLIST *queue = qu;
    llist_destroy(queue);
}
