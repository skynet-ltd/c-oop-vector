#pragma once
#include <stdio.h>
#ifdef __JEMALLOC_ON__
#include <jemalloc/jemalloc.h>
#else
#include <stdlib.h>
#endif

typedef struct vector
{
    void **data;
    unsigned int size;
    unsigned int used;
    unsigned int type_size;
    int (*push)(struct vector *self, void *elem);
    int (*shift)(struct vector *self, void *elem);
    void *(*pop)(struct vector *self);
    void *(*unshift)(struct vector *self);
    void *(*get)(struct vector *self, int index);
    void (*clear)(struct vector *self, int full);
    int (*length)(struct vector *self);
    int (*cap)(struct vector *self);
} vector;

int push(vector *self, void *elem);
int shift(vector *self, void *elem);
void *unshift(vector *self);
void *get(vector *self, int index);
void *pop(vector *self);
int length(vector *self);
int cap(vector *self);

vector *new_vector(unsigned int type_size, unsigned int size);
void clear(vector *self, int full);