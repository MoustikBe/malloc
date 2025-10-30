#ifndef MALLOC_H
# define MALLOC_H

#define TINY_SIZE 512
#define SMALL_SIZE 2048

#include "main.h"

typedef struct block
{
    size_t  bytes;
    bool    free;
    void    *data;
    struct block   *next;
} block;


void *ft_malloc(size_t size);

#endif