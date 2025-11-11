/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaac-c <misaac-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 20:27:30 by misaac-c          #+#    #+#             */
/*   Updated: 2025/11/11 10:02:51 by misaac-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int dig)
{
	if ((dig >= 48) && (dig <= 57))
	{
		return (dig);
	}
	else
	{
		return (0);
	}
}
/*
int main (void)
{
	int result; 
	result = ft_isdigit('\001');
	ft_printf("%d\n", result);
}
*/
