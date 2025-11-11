/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaac-c <misaac-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 19:13:47 by misaac-c          #+#    #+#             */
/*   Updated: 2025/11/11 10:02:58 by misaac-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			count;
	unsigned char	*str;

	count = 0;
	str = ((unsigned char *)s);
	while (count < n)
	{
		if (str[count] == (unsigned char)c)
			return (str + count);
		count++;
	}
	return (NULL);
}
/*
int main() 
{
    char str[] = "Hello, World!";
    char *result = memchr(str, 'o', strlen(str));
	char *result2 = ft_memchr(str, 'o', strlen(str));

   	ft_printf("%s\n", (char *)result);
    ft_printf("%s\n", (char *)result); 
}
*/
