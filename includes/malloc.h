#ifndef MALLOC_H
# define MALLOC_H

#include "main.h"

static inline size_t get_page_size(void)
{
    return( sysconf(_SC_PAGESIZE));
}

#define TINY_SIZE (get_page_size() * 4)
#define SMALL_SIZE (get_page_size() * 32)

#define TINY_ZONE (((TINY_SIZE) + sizeof(block)) * 100)
#define SMALL_ZONE (((SMALL_SIZE) + sizeof(block)) * 100)

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

/* SHOW_MEM */
void    show_alloc_mem(void);
/* MALLOC */
bool	extend_memory(block **_block, int type);
void	*malloc(size_t size);
void	*prepare_list(block **_block, size_t size, int type);
void	*large_list(size_t size);
void	*give_addr(block **_block, size_t size, int type);
block	*create_list(void *zone, int type);
/* REALLOC */
void	*realloc(void *ptr, size_t size);
/* FREE */
void	free(void  *pointer);

#endif