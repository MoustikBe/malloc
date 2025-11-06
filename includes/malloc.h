#ifndef MALLOC_H
# define MALLOC_H

#define TINY_SIZE 512
#define SMALL_SIZE 2048

#define TINY_ZONE (TINY_SIZE + sizeof(block)) * 100
#define SMALL_ZONE (SMALL_SIZE + sizeof(block)) * 100

#include "main.h"

typedef struct block
{
    size_t			bytes;
    bool			free;
    struct block	*next;
} block;

typedef struct malloc_list
{
    block	*tiny_head;
    block	*small_head;
    block	*large_head;
} malloc_list;

extern malloc_list l_malloc;

/* MALLOC */
bool	extend_memory(block **_block, int type);
void	*ft_malloc(size_t size);
void	*prepare_list(block **_block, size_t size, int type);
void	*large_list(size_t size);
void	*give_addr(block **_block, size_t size, int type);
block	*create_list(void *zone, int type);
/* REALLOC */
void	*ft_realloc(void *ptr, size_t size);
/* FREE */
void	ft_free(void  *pointer);

#endif