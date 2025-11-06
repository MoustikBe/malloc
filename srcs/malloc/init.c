/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaac-c <misaac-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 12:23:50 by misaac-c          #+#    #+#             */
/*   Updated: 2025/11/06 13:03:04 by misaac-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/malloc.h"

/* Function that create the list, in case is the first time malloc is used. */
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

/* Function that ask the system to give us [ZONE] of memory, [ZONE] will be used after to create the list that match with [SIZE] requested by malloc. */
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

/* Function that handle the specific case of large_list. large allocation use mmap to allocate the exact [SIZE] in [ZONE] + (metadata) for the list. */
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
