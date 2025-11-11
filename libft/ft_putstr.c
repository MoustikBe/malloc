/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaac-c <misaac-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 18:10:33 by misaac-c          #+#    #+#             */
/*   Updated: 2025/11/11 10:01:55 by misaac-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr(char *s, int *count_2)
{
	int	i;

	i = 0;
	if (s == NULL)
	{
		ft_putstr("(null)", count_2);
		return ;
	}
	while (s[i])
		ft_putchar((int)s[i++], count_2);
}
