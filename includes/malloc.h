#ifndef MALLOC_H
# define MALLOC_H

#define BLOCK_SIZE 4096

#include "main.h"

typedef struct block
{
    size_t  bytes;
    bool    free;
    struct block   *next;
    void    *data;
} block;


void *ft_malloc(size_t size);

#endif