/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaac-c <misaac-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 18:37:23 by misaac-c          #+#    #+#             */
/*   Updated: 2025/11/11 10:03:06 by misaac-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		count;
	char	*src;

	src = (char *)s;
	count = 0;
	while (src[count] != '\0')
	{
		if (src[count] == (char)c)
			return (&src[count]);
		count++;
	}
	if ((char)c == '\0')
		return (&src[count]);
	return (NULL);
}
/*
int main(void)
{
	const char str1[] = "";
	const char st1[] = "";
	//char str2 = *ft_strchr(str1, 'a');
	char st2 = *strchr(st1, 'a');
	//ft_printf("%c\n", str2);
	ft_printf("%c\n", st2);
}
*/
