/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaac-c <misaac-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 17:58:08 by misaac-c          #+#    #+#             */
/*   Updated: 2025/11/11 10:02:18 by misaac-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_menu_variable(char *str, va_list *argv, int count, int *count_2)
{
	if (str[count] == 'c')
		ft_putchar(va_arg(*argv, int), count_2);
	else if (str[count] == 's')
		ft_putstr(va_arg(*argv, char *), count_2);
	else if (str[count] == 'd' || str[count] == 'i')
		ft_putnbr(va_arg(*argv, int), count_2);
	else if (str[count] == 'u')
		ft_unsigned(va_arg(*argv, unsigned int), count_2);
	else if (str[count] == 'p')
		ft_ptr(va_arg(*argv, size_t), count_2);
	else if (str[count] == 'x')
		ft_hexadecimal(va_arg(*argv, unsigned int),
			"0123456789abcdef", count_2);
	else if (str[count] == 'X')
		ft_hexadecimal(va_arg(*argv, unsigned int),
			"0123456789ABCDEF", count_2);
	else if (str[count] == '%')
		ft_putchar('%', count_2);
}

int	ft_printf(const char *str, ...)
{
	va_list	argv;
	int		count;
	int		count_2;

	count = 0;
	count_2 = 0;
	va_start(argv, str);
	while (str[count])
	{
		if (str[count] == '%')
		{
			ft_menu_variable((char *)str, &argv, ++count, &count_2);
			count++;
			if (count_2 == -1)
				return (-1);
		}
		else
			ft_putchar((int)str[count++], &count_2);
	}
	va_end(argv);
	return (count_2);
}
