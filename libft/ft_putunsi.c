/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunsi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaac-c <misaac-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 18:10:36 by misaac-c          #+#    #+#             */
/*   Updated: 2025/11/11 10:01:57 by misaac-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_unsigned(unsigned int nbr, int *count_2)
{
	if (nbr > 9)
	{
		ft_putnbr(nbr / 10, count_2);
		ft_putchar(nbr % 10 + '0', count_2);
	}
	else
		ft_putchar(nbr + '0', count_2);
}
