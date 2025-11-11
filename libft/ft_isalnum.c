/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaac-c <misaac-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 18:41:09 by misaac-c          #+#    #+#             */
/*   Updated: 2025/11/11 10:02:50 by misaac-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int alph)
{
	if (((alph >= 65) && (alph <= 90)) || ((alph >= 97) && (alph <= 122)))
		return (1);
	else if ((alph >= 48) && (alph <= 57))
		return (1);
	else
		return (0);
}
/*
int main(void)
{
	int result;
	result = ft_isalnum('\001');
	ft_printf("%d\n", result); 
}
*/
