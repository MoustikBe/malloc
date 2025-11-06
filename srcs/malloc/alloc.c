/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaac-c <misaac-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 12:40:24 by misaac-c          #+#    #+#             */
/*   Updated: 2025/11/06 12:47:12 by misaac-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/malloc.h"

void alloc_extension(block **_block, int type, void *zone, size_t nb_block)
{
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
    {
        *_block = create_list(zone, type);
        return (true);
    }
    alloc_extension(_block, type, zone, nb_block);
    return(true);
}

void *give_addr(block **_block, size_t size, int type)
{
    void    *addr_malloc = NULL;
    block   *current = *_block;

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
