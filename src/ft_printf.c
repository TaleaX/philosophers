/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdehne <tdehne@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 16:31:10 by tdehne            #+#    #+#             */
/*   Updated: 2022/11/27 02:07:53 by tdehne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

static int	ft_process_arg(char c, va_list arg)
{
	if (c == 's')
		return (write_s(arg));
	if (c == 'i' || c == 'd' || c == 'c')
		return (write_c_i(arg, c));
	if (c == 'u')
		return (write_u(arg));
	if (c == 'p')
		return (write_p(arg, "0123456789abcdef"));
	if (c == 'x')
		return (write_x_uppx(arg, "0123456789abcdef"));
	if (c == 'X')
		return (write_x_uppx(arg, "0123456789ABCDEF"));
	if (c == '%')
		return (write(1, "%", 1));
	return (0);
}

int	ft_printf(const char *str, ...)
{
	va_list	argptr;
	int		counter;

	va_start(argptr, str);
	counter = 0;
	while (*str)
	{
		if (*str == '%')
		{
			str++;
			counter--;
			if (!*str)
				break ;
			counter += ft_process_arg(*str, argptr);
		}
		else
			write(1, str, 1);
		str++;
		counter++;
	}
	va_end(argptr);
	return (counter);
}
