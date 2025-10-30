#include "../includes/malloc.h"

/*
Malloc:
    in case of error -> return NULL
    try to allocate [size] in a pointer that the function create 
    and return the ptr create with [size] of memory created

    use mmap() -> mmap is a function that create the memory
    mmap(NULL, sizeof(char) * 100, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
*/


static block *tiny_head = NULL;
static block *small_head = NULL;
static block *large_head = NULL;

block   *create_list(void *zone, int type)
{
    block *head = (block *) zone;
    block *current = head;
    size_t nb_block;

    if(type == 1)
        nb_block = TINY_ZONE / (TINY_SIZE + sizeof(block));
    else
        nb_block = SMALL_ZONE / (SMALL_SIZE + sizeof(block));
    for(size_t i = 0; i < nb_block ; i++)
    {
        if(type == 1)
            current->bytes = TINY_SIZE;
        else
            current->bytes = SMALL_SIZE;
        current->free = true;
        
        if(i < nb_block - 1)
        {
            if(type == 1)
                current->next = (block *)((char *)current + sizeof(block) + TINY_SIZE);
            else
                current->next = (block *)((char *)current + sizeof(block) + SMALL_SIZE);
        }
        else 
            current->next = NULL; 
        current = current->next;
    }
    return(head);
}

bool extend_memory(block **_block, int type)
{
    void *zone;
    size_t nb_block;

    if(type == 1)
    {
        zone = mmap(NULL, TINY_ZONE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
        nb_block = TINY_ZONE / (TINY_SIZE + sizeof(block));
    }
    else
    {
        zone = mmap(NULL, SMALL_ZONE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
        nb_block = SMALL_ZONE / (SMALL_SIZE + sizeof(block));
    }
    if(zone == MAP_FAILED)
        return false;
    if(!*_block)
        *_block = create_list(zone, type);
    block *current = *_block;
    
    while (current->next)
        current = current->next;
    
    block *new = (block *) zone;
    current->next = new;
    for(size_t i = 0; i < nb_block ; i++)
    {
        if(type == 1)
            new->bytes = TINY_SIZE;
        else
            new->bytes = SMALL_SIZE;
        new->free = true;
        if(i < nb_block - 1)
        {
            if(type == 1)    
                new->next = (block *)((char *)new + sizeof(block) + TINY_SIZE);
            else 
                new->next = (block *)((char *)new + sizeof(block) + SMALL_SIZE);
        }
        else 
            new->next = NULL; 
        new = new->next;
    }
    return(true);
}

void *give_addr(block **_block, size_t size, int type)
{
    void *addr_malloc = NULL;
    block *current = *_block;

    while(current)
    {
        if(current->free && size <= current->bytes)
        {
            addr_malloc = (void *)(current + 1);
            if(size == current->bytes)
            {
                current->bytes = 0;
                current->free = false;
            }
            else 
            {
                block *new = (block *)((char *)(current + 1) + size);
                new->bytes = current->bytes - size - sizeof(block);
                new->free = true;
                new->next = current->next;

                current->next = new;
                current->bytes = size;
                current->free = false;
            }
            break;
        }
        else
            current = current->next;
    }
    if(!addr_malloc)
    {
        if(!extend_memory(&_block, type))
            return (NULL);
        addr_malloc = give_addr(_block, size, type);
    }
    return (addr_malloc);
}

void    *prepare_list(block **_block, size_t size, int type)
{
    void *zone;

    if(!_block)
    {
        if(type == 1)
            zone = mmap(NULL, TINY_ZONE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
        else
            zone = mmap(NULL, SMALL_ZONE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
        if(zone == MAP_FAILED)
            return(NULL);
        _block = create_list(zone, type);
    }
    return(give_addr(_block, size, type));
}

void    *large_list(size_t size)
{
    void *zone;

    zone = mmap(NULL, size + sizeof(block), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if(zone == MAP_FAILED)
        return (NULL);
    block *last;
    if(large_head)
    {
        block *current = large_head;
        while(current->next)
            current = current->next;
        last = (block *)zone;
        last->free = false;
        last->bytes = size;
        last->next = NULL;
        current->next = last;
    }
    else 
    {
        large_head = (block *)zone;
        large_head->bytes = size;
        large_head->free = false;
        large_head->next = NULL;
        last = large_head;
    }
    return((void *)((char *)last + sizeof(block)));
}


/* FREE */
void ft_free(void   *pointer)
{
    block *_block = (block *)pointer - 1;
    block *next = _block->next;
    block *current;

    /* CAS LARGE IN PROGRESS */
    if(_block->bytes > SMALL_SIZE)
    {
        if(_block == large_head)
        {
            large_head = NULL;
            munmap(pointer, strlen(pointer));
            return ;
        }
        current = large_head;
        while (current && current->next != _block)
            current = current->next;
        if(current)
            current = _block->next;
        munmap(pointer, strlen(pointer));
        return ;
    }
    /* CAS LARGE IN PROGRESS */
    
    _block->free = true;
    if(next && next->free)
    {
        _block->bytes += sizeof(block) + next->bytes;
        _block->next = next->next;
    }

    current = tiny_head;
    while (current && current->next != _block)
        current = current->next;
    if(current && current->free)
    {
        current->bytes += sizeof(block) + _block->bytes;
        current->next = _block->next;
    }

    return ;
}
/* FREE */

void *ft_malloc(size_t size)
{   
    void *zone;
    if(!size)
        return(NULL);

    if(size <= TINY_SIZE)
        return(prepare_list(&tiny_head, size, 1));
    else if(size > TINY_SIZE && size <= SMALL_SIZE)
        return(prepare_list(&small_head, size, 2));
    else
        return(large_list(size));
}
