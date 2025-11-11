/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaac-c <misaac-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 12:44:59 by misaac-c          #+#    #+#             */
/*   Updated: 2025/11/11 10:02:50 by misaac-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*mem;

	mem = malloc(count * size);
	if (mem == NULL)
		return (mem);
	if (count >= SIZE_MAX || size >= SIZE_MAX)
		return (NULL);
	ft_bzero(mem, count * size);
	return (mem);
}
/*
int main() 
{
    ft_printf("%p\n", ft_calloc(SIZE_MAX, SIZE_MAX));
    ft_printf("%p\n", calloc(SIZE_MAX, SIZE_MAX));
}
*/
