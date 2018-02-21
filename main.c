#include <stdio.h>
#include <stdlib.h>

typedef struct vector
{
      void **data;
      unsigned int size;
      unsigned int used;
      unsigned int type_size;
      void (*push)(struct vector *self, void *elem);
      void (*shift)(struct vector *self, void *elem);
      void *(*pop)(struct vector *self);
      void *(*unshift)(struct vector *self);
      void *(*get)(struct vector *self, int index);
      void (*clear)(struct vector *self);
      int (*length)(struct vector *self);
      int (*cap)(struct vector *self);
} vector;

void push(vector *self, void *elem)
{
      self->used++;
      if (self->used == self->size)
      {
            self->size = self->size * 2;
            self->data = realloc(self->data, self->size * self->type_size * sizeof(char));
      }
      char **vec = (char **)self->data;
      vec += sizeof(char) * (self->type_size * (self->used - 1));
      *vec = elem;
}

void shift(vector *self, void *elem)
{
      self->used++;
      if (self->used == self->size)
      {
            self->size = self->size * 2;
            self->data = realloc(self->data, self->size * self->type_size * sizeof(char));
      }
      char **vec = (char **)self->data;
      vec += sizeof(char) * self->type_size * self->used;
      for (int i = self->used; i > 0; i--)
      {
            *vec = *(vec - sizeof(char) * self->type_size);
            vec -= sizeof(char) * self->type_size;
      }
      *vec = elem;
}

void *unshift(vector *self)
{
      if (self->used > 0)
      {
            char **vec = (char **)self->data;
            char *ret = (void *)*vec;
            for (int i = 0; i < self->used - 1; i++)
            {
                  *vec = *(vec + sizeof(char) * self->type_size);
                  vec += sizeof(char) * self->type_size;
            }
            self->used--;
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
      vec += sizeof(char) * (self->type_size * index);
      return (void *)*vec;
}

void *pop(vector *self)
{
      if (self->used > 0)
      {
            char **vec = (char **)self->data;
            vec += sizeof(char) * (self->type_size * (self->used - 1));
            self->used--;
            return (void *)*vec;
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

void clear(vector *self)
{
      free(self->data);
      free(self);
}

vector *new_vector(unsigned int type_size, unsigned int size)
{
      if (size == 0)
      {
            size = 1;
      }
      vector *vec = NULL;
      vec = calloc(1, sizeof(vector));
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

int main(int argc, char const *argv[])
{
      vector *vec = new_vector(sizeof(char *), 10);
      vec->push(vec, "Hello world6!");
      vec->shift(vec, "Hello world5!");
      vec->shift(vec, "Hello world4!");
      printf("%s\n", (const char *)vec->get(vec, 0));
      printf("%s\n", (const char *)vec->get(vec, 1));
      printf("%s\n", (const char *)vec->get(vec, 2));
      printf("Unshift\n");
      printf("%s\n", (const char *)vec->unshift(vec));
      printf("%s\n", (const char *)vec->unshift(vec));
      printf("%s\n", (const char *)vec->unshift(vec));
      vec->clear(vec);
      return 0;
}
