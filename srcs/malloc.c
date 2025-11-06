#include "../includes/malloc.h"

/*
Malloc:
    in case of error -> return NULL
    try to allocate [size] in a pointer that the function create 
    and return the ptr create with [size] of memory created

    use mmap() -> mmap is a function that create the memory
    mmap(NULL, sizeof(char) * 100, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
*/



void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	count;

	count = 0;
	if (dst == NULL && src == NULL)
		return (NULL);
	while (count < n)
	{
		((unsigned char *)dst)[count] = ((unsigned char *)src)[count];
		count++;
	}
	return (dst);
}

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
    if(!*_block) {
        *_block = create_list(zone, type);
        return (true);
    }
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
            size_t remaining = current->bytes - size;
            addr_malloc = (void *)(current + 1);
            if(size == current->bytes || remaining <= sizeof(block))
            {
                current->free = false;
                current->bytes = size;
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
        if(!extend_memory(_block, type))
            return (NULL);
        addr_malloc = give_addr(_block, size, type);
    }
    return (addr_malloc);
}

void    *prepare_list(block **_block, size_t size, int type)
{
    void *zone;

    if(!*_block)
    {
        if(type == 1)
            zone = mmap(NULL, TINY_ZONE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
        else
            zone = mmap(NULL, SMALL_ZONE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
        if(zone == MAP_FAILED)
            return(NULL);
        *_block = create_list(zone, type);
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
    if(l_malloc.large_head)
    {
        block *current = l_malloc.large_head;
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
        l_malloc.large_head = (block *)zone;
        l_malloc.large_head->bytes = size;
        l_malloc.large_head->free = false;
        l_malloc.large_head->next = NULL;
        last = l_malloc.large_head;
    }
    return((void *)((char *)last + sizeof(block)));
}


/* FREE */
void ft_free(void   *pointer)
{
    if(!pointer)
        return;
    block *_block = (block *)pointer - 1;
    //printf("address -> %p, bytes -> %zu, free ? %d\n", &_block, _block->bytes, _block->free);
    block *next = _block->next;
    block *current;

    if(_block->bytes > SMALL_SIZE)
    {
        if(_block == l_malloc.large_head)
            l_malloc.large_head = l_malloc.large_head->next;
        else 
        {
            current = l_malloc.large_head;
            while (current && current->next != _block)
                current = current->next;
            if(current)
                current->next = _block->next;
        }
        munmap(_block, sizeof(block) + _block->bytes);
        return ;
    }

    
    _block->free = true;
    if(next && next->free)
    {
        _block->bytes += sizeof(block) + next->bytes;
        _block->next = next->next;
    }

    if(_block->bytes <= TINY_SIZE)
        current = l_malloc.tiny_head;
    else
        current = l_malloc.small_head;

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

bool verif_in_list(void *ptr)
{
    block *current;

    for(int i = 0; i < 3; i++)
    {
        if(i == 0)
            current = l_malloc.tiny_head;
        else if(i == 1)
            current = l_malloc.small_head;
        else
            current = l_malloc.large_head;
        while(current)
        {
            if((void *)(current + 1) == ptr)
                return(true);
            current = current->next;
        }
    }
    return(false);
}

void *ft_realloc(void *ptr, size_t size)
{
    void *addr_malloc;
    block *_block = (block *)ptr - 1;
    if(!ptr)
        return(ft_malloc(size));
    else if(!verif_in_list(ptr))
        return(NULL);
    else if(size == 0)
        return(ft_free(ptr), NULL);
    else if(size <= _block->bytes + sizeof(block))
        return(ptr);

    block *next = _block->next;
    if(next && next->free && (_block->bytes + next->bytes + sizeof(block) >= size))
    {
        _block->bytes += next->bytes + sizeof(block);
        _block->next = next->next;
        if(size +sizeof(block) < _block->bytes)
        {
            block *new = (block *)((char *)(_block + 1) + size);
            new->bytes = _block->bytes - size - sizeof(block);
            new->free = true;
            new->next = _block->next;

            _block->next = new;
            _block->bytes = size;
        }
        _block->free = false;
        return((void *)(_block + 1));
    }
    addr_malloc = ft_malloc(size);
    if(!addr_malloc)
        return(NULL);
    ft_memcpy(addr_malloc, ptr, size);
    ft_free(ptr);
    return(addr_malloc);
}

void *ft_malloc(size_t size)
{   
    if(!size)
        return(NULL);

    if(size <= TINY_SIZE)
        return(prepare_list(&l_malloc.tiny_head, size, 1));
    else if(size > TINY_SIZE && size <= SMALL_SIZE)
        return(prepare_list(&l_malloc.small_head, size, 2));
    else
        return(large_list(size));
}
