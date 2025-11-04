#ifndef MALLOC_H
# define MALLOC_H

#define TINY_SIZE 512
#define SMALL_SIZE 2048

#define TINY_ZONE (TINY_SIZE + sizeof(block)) * 100
#define SMALL_ZONE (SMALL_SIZE + sizeof(block)) * 100

#include "main.h"

typedef struct block
{
    size_t  bytes;
    bool    free;
    struct block   *next;
} block;


void *ft_malloc(size_t size);
void *ft_realloc(void *ptr, size_t size);
void ft_free(void  *pointer);

#endif