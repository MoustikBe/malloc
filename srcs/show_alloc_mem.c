/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaac-c <misaac-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 13:09:55 by misaac-c          #+#    #+#             */
/*   Updated: 2025/11/06 16:05:49 by misaac-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void    show_alloc_mem()
{
    block *current;
    
    current = l_malloc.tiny_head;
    for(int i = 0; current; i++)
    {
        if(!current->free)
            printf("Memory allocated from tiny at address -> %p with %zu, number of bytes.\n", &current, current->bytes);
        current = current->next;
    }
    current = l_malloc.small_head;
    for(int i = 0; current; i++)
    {
        if(!current->free)
            printf("Memory allocated from small at address -> %p with %zu, number of bytes.\n", &current, current->bytes);
        current = current->next;
    }
    current = l_malloc.large_head;
    for(int i = 0; current; i++)
    {
        if(!current->free)
            printf("Memory allocated from large at address -> %p with %zu, number of bytes.\n", &current, current->bytes);
        current = current->next;
    }
}