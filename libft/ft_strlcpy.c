/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaac-c <misaac-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 17:28:12 by misaac-c          #+#    #+#             */
/*   Updated: 2025/11/11 10:03:08 by misaac-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	count;

	count = 0;
	if (dstsize == 0)
		return (ft_strlen(src));
	while (src[count] != '\0' && count < dstsize - 1)
	{
		dst[count] = src[count];
		count++;
	}
	dst[count] = '\0';
	while (src[count] != '\0')
		count++;
	return (ft_strlen(src));
}
/*
int		main(void)
{
	char	dest[50];
	char	*src;
	int		size;

	src = "ceci et un test tu voissss";
	size = 10;
	ft_printf("%d\n", ft_strlcpy(dest, src, size));
	ft_printf(".%s.\n\n", dest);
	ft_printf("%lu\n", strlcpy(dest, src, size));
	ft_printf(".%s.\n\n", dest);
}
*/
