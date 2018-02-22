#include "vector.h"

int push(vector *self, void *elem)
{
    self->used++;
    if (self->used == self->size)
    {
        self->size = self->size * 2;
        void **tmp_ptr = realloc(self->data, (size_t)(self->size * self->type_size * sizeof(char)));
        if (!tmp_ptr)
        {
            return -1;
        }
        self->data = tmp_ptr;
    }
    char **vec = (char **)self->data;
    vec += sizeof(char) * (self->type_size * (self->used - 1));
    *vec = elem;
    return 0;
}

int shift(vector *self, void *elem)
{
    self->used++;
    if (self->used == self->size)
    {
        self->size = self->size * 2;
        void **tmp_ptr = realloc(self->data, (size_t)(self->size * self->type_size * sizeof(char)));
        if (!tmp_ptr)
        {
            return -1;
        }
        self->data = tmp_ptr;
    }
    char **vec = (char **)self->data;
    vec += sizeof(char) * self->type_size * self->used;
    for (int i = self->used; i > 0; i--)
    {
        *vec = *(vec - sizeof(char) * self->type_size);
        vec -= sizeof(char) * self->type_size;
    }
    *vec = elem;
    return 0;
}

void *unshift(vector *self)
{
    if (self->used > 0)
    {
        char **vec = (char **)self->data;
        char *ret = (void *)*vec;
        self->used--;
        free(*vec);
        for (int i = 0; i < self->used; i++)
        {
            *vec = *(vec + sizeof(char) * self->type_size);
            vec += sizeof(char) * self->type_size;
        }
        return ret;
    }
    return NULL;
}

void *get(vector *self, int index)
{
    if (index > self->used - 1 || index < 0)
    {
        return NULL;
    }
    char **vec = (char **)self->data;
    return (void *)*(vec + sizeof(char) * (self->type_size * index));
}

void *pop(vector *self)
{
    if (self->used > 0)
    {
        char **vec = (char **)self->data;
        vec += sizeof(char) * (self->type_size * (self->used - 1));
        void *ret = (void *)*vec;
        self->used--;
        free(*vec);
        return ret;
    }
    return NULL;
}

int length(vector *self)
{
    return self->used;
}

int cap(vector *self)
{
    return self->size;
}

void clear(vector *self, int full)
{
    if (full)
    {
        char **vec = (char **)self->data;
        for (int i = 0; i < self->length(self); i++)
        {
            free(*(vec + self->type_size * sizeof(char) * i));
        }
    }
    free(self->data);
    free(self);
}

vector *new_vector(unsigned int type_size, unsigned int size)
{
    if (size < 4096)
    {
        size = 4096;
    }
    vector *vec = calloc(1, sizeof(vector));
    vec->type_size = type_size;
    vec->size = size;
    vec->used = 0;
    vec->data = calloc(vec->type_size * vec->size * sizeof(char), vec->type_size * vec->size * sizeof(char));
    vec->push = push;
    vec->get = get;
    vec->pop = pop;
    vec->shift = shift;
    vec->unshift = unshift;
    vec->clear = clear;
    vec->length = length;
    vec->cap = cap;
    return vec;
}