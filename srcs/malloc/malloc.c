/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaac-c <misaac-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 12:43:26 by misaac-c          #+#    #+#             */
/*   Updated: 2025/11/06 12:53:40 by misaac-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/malloc.h"

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
