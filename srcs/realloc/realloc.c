/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaac-c <misaac-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 12:09:19 by misaac-c          #+#    #+#             */
/*   Updated: 2025/11/06 13:06:17 by misaac-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/malloc.h"

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

/* Function that check if the memory allocated is from this malloc implementation. */
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

void *realloc(void *ptr, size_t size)
{
    void *addr_malloc;
    block *_block = (block *)ptr - 1;
    if(!ptr)
        return(malloc(size));
    else if(!verif_in_list(ptr))
        return(NULL);
    else if(size == 0)
        return(free(ptr), NULL);
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
    addr_malloc = malloc(size);
    if(!addr_malloc)
        return(NULL);
    ft_memcpy(addr_malloc, ptr, size);
    free(ptr);
    return(addr_malloc);
}
