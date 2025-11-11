/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaac-c <misaac-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 01:11:37 by misaac-c          #+#    #+#             */
/*   Updated: 2025/11/11 10:03:12 by misaac-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	count;

	count = 0;
	if (!n)
		return (0);
	while (count < n && s1[count] && s2[count]
		&& (unsigned char)s1[count] == (unsigned char)s2[count])
		count++;
	if (count < n)
		return ((unsigned char)s1[count] - (unsigned char)s2[count]);
	else
		return (0);
}
/*
int main(void)
{
	const char str1[] = "Bonjour";
	const char str2[] = "jour";

	char st1[] = "Bonjour";
	char st2[] = "jour";

	int result = ft_strncmp(str1, str2, 50);
	int result2 = strncmp(st1, st2, 50);
	ft_printf("%d\n", result);
	ft_printf("%d\n", result2);
}
*/
