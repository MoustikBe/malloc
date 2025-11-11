/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaac-c <misaac-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 17:48:50 by misaac-c          #+#    #+#             */
/*   Updated: 2025/11/11 10:02:59 by misaac-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	count;

	count = 0;
	while (count != len)
	{
		((unsigned char *)b)[count] = ((unsigned char )c);
		count++;
	}
	return (b);
}
/*
int main(void)
{
	char c[5] = "AAAA";
	char d[5]  = "AAAA";
	ft_memset(c+2, 'B', 2);
	memset(d+2, 'B', 2);
	ft_printf("%s\n", c);
	ft_printf("%s\n", d);
}
*/
