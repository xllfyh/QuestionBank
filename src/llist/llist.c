#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "llist.h"

struct llist_node_st
{
    struct llist_node_st *prev;
    struct llist_node_st *next;
    char data[1];
};

struct llist_head_st
{
    int size;
    struct llist_node_st head;
};

LLIST *llist_create(int size)
{
    struct llist_head_st *l;

    l = malloc(sizeof(*l));
    if (l == NULL)
        return NULL;

    l->size = size;
    l->head.prev = l->head.next = &l->head;

    return l;
}

int llist_insert(LLIST *l, const void *data, int mode)
{
    struct llist_head_st *ptr = l;
    struct llist_node_st *node;

    node = malloc(sizeof(*node) + ptr->size);
    if (node == NULL)
        return -1;
    memcpy(node->data, data, ptr->size);

    if (mode == LLIST_FORWARD)
    {
        node->prev = &ptr->head;
        node->next = ptr->head.next;
    }
    else if (mode == LLIST_BACKWARD)
    {
        node->prev = ptr->head.prev;
        node->next = &ptr->head;
    }
    else
    {
        free(node);
        return -3;
    }

    node->prev->next = node;
    node->next->prev = node;
    return 0;
}

static struct llist_node_st *find_(struct llist_head_st *ptr, const void *key, llist_cmp *cmp)
{
    struct llist_node_st *cur;

    for (cur = ptr->head.next; cur != &ptr->head; cur = cur->next)
    {
        if (cmp(cur->data, key) == 0)
            break;
    }

    return cur;
}

void *llist_find(LLIST *l, const void *key, llist_cmp *cmp)
{
    struct llist_head_st *ptr = l;
    struct llist_node_st *node;

    node = find_(ptr, key, cmp);
    if (node == &ptr->head)
        return NULL;
    return node->data;
}

int llist_delete(LLIST *l, const void *key, llist_cmp *cmp)
{
    struct llist_head_st *ptr = l;
    struct llist_node_st *node;

    node = find_(ptr, key, cmp);
    if (node == &ptr->head)
        return -1;

    node->prev->next = node->next;
    node->next->prev = node->prev;
    free(node);
    return 0;
}

int llist_fetch(LLIST *l, const void *key, llist_cmp *cmp, void *datap)
{
    struct llist_head_st *ptr = l;
    struct llist_node_st *node;

    node = find_(ptr, key, cmp);
    if (node == &ptr->head)
        return -1;

    memcpy(datap, node->data, ptr->size);

    node->prev->next = node->next;
    node->next->prev = node->prev;
    free(node);
    return 0;
}

void llist_travel(LLIST *l, llist_op *op)
{
    struct llist_head_st *ptr = l;
    struct llist_node_st *cur;

    for (cur = ptr->head.next; cur != &ptr->head; cur = cur->next)
    {
        op(cur->data);
    }
}

void llist_destroy(LLIST *l)
{
    struct llist_head_st *ptr = l;
    struct llist_node_st *cur;
    struct llist_node_st *next;

    for (cur = ptr->head.next; cur != &ptr->head; cur = next)
    {
        next = cur->next;
        free(cur);
    }

    free(ptr);
}
