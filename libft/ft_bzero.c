/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaac-c <misaac-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 18:49:41 by misaac-c          #+#    #+#             */
/*   Updated: 2025/11/11 10:02:49 by misaac-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	count;

	count = 0;
	while (count != n)
	{
		((unsigned char *)s)[count] = 0;
		count++;
	}
}
/*
int main(void)
{
	char c[5] = "AAAA";
	char d[5]  = "AAAA";
	ft_bzero(c, 2);
	bzero(d, 2);	
	ft_printf("%s\n", c);
	ft_printf("%s\n", d);
	return(0);
}
*/
