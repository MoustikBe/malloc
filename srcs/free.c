/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaac-c <misaac-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 12:09:17 by misaac-c          #+#    #+#             */
/*   Updated: 2025/11/06 12:16:26 by misaac-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

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