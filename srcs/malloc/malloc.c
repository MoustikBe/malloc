/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaac-c <misaac-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 12:43:26 by misaac-c          #+#    #+#             */
/*   Updated: 2025/11/06 12:49:38 by misaac-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/malloc.h"

/*
Malloc:
    in case of error -> return NULL
    try to allocate [size] in a pointer that the function create 
    and return the ptr create with [size] of memory created

    use mmap() -> mmap is a function that create the memory
    mmap(NULL, sizeof(char) * 100, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
*/

malloc_list l_malloc = {NULL, NULL, NULL};

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
