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

void show_alloc_mem(void)
{
    block *current;

    printf("TINY : %p\n", (void *)l_malloc.tiny_head);
    current = l_malloc.tiny_head;
    while (current)
    {
        if (!current->free)
        {
            void *start = (void *)(current + 1);
            void *end = (void *)((char *)(current + 1) + current->bytes);
            printf("%p - %p : %zu bytes\n", start, end, current->bytes);
        }
        current = current->next;
    }

    printf("SMALL : %p\n", (void *)l_malloc.small_head);
    current = l_malloc.small_head;
    while (current)
    {
        if (!current->free)
        {
            void *start = (void *)(current + 1);
            void *end = (void *)((char *)(current + 1) + current->bytes);
            printf("%p - %p : %zu bytes\n", start, end, current->bytes);
        }
        current = current->next;
    }

    printf("LARGE : %p\n", (void *)l_malloc.large_head);
    current = l_malloc.large_head;
    while (current)
    {
        if (!current->free)
        {
            void *start = (void *)(current + 1);
            void *end = (void *)((char *)(current + 1) + current->bytes);
            printf("%p - %p : %zu bytes\n", start, end, current->bytes);
        }
        current = current->next;
    }
}
