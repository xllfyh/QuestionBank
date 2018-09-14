
#ifndef LLIST_H__
#define LLIST_H__

typedef void LLIST;

#define LLIST_FORWARD 1
#define LLIST_BACKWARD 2

typedef void llist_op(const void *);
typedef int llist_cmp(const void *, const void *);

LLIST *llist_create(int size);
int llist_insert(LLIST *l, const void *data, int mode);
void *llist_find(LLIST *l, const void *key, llist_cmp *cmp);
int llist_delete(LLIST *l, const void *key, llist_cmp *cmp);
int llist_fetch(LLIST *l, const void *key, llist_cmp *cmp, void *datap);
void llist_travel(LLIST *l, llist_op *op);
void llist_destroy(LLIST *l);


#endif
