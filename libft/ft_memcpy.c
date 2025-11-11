/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaac-c <misaac-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 19:20:26 by misaac-c          #+#    #+#             */
/*   Updated: 2025/11/11 10:02:58 by misaac-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	count;

	count = 0;
	if (dst == NULL && src == NULL)
		return (NULL);
	while (count < n)
	{
		((unsigned char *)dst)[count] = ((unsigned char *)src)[count];
		count++;
	}
	return (dst);
}
/*
int main (void)
{
	char a[5] = "";
	char b[5] = "";
	char c[5] = "ABCD";
	char d[5]  = "EFGH";
	ft_memcpy(a, c, 3);
	memcpy(b, d, 3);
	ft_printf("%s\n", c);
	ft_printf("%s\n", d);
}
*/
