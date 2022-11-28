/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdehne <tdehne@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 09:29:24 by tdehne            #+#    #+#             */
/*   Updated: 2022/11/27 02:08:02 by tdehne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

static int	log_10(unsigned int num)
{
	unsigned int	counter;

	counter = 0;
	num /= 10;
	while (num != 0)
	{
		num /= 10;
		counter++;
	}
	return (counter);
}

static int	pow_of(int base, int exp)
{
	int		result;

	result = 1;
	while (exp > 0)
	{
		result *= base;
		exp--;
	}
	return (result);
}

int	putuint_fd(unsigned int n, int fd)
{
	int	digit;
	int	exp;
	int	counter;

	exp = log_10(n);
	counter = 0;
	while (exp >= 0)
	{
		digit = ((n / pow_of(10, exp)) % 10) + 48;
		write(fd, &digit, 1);
		counter++;
		exp--;
	}
	return (counter);
}

int	putnbr_count(int n)
{
	int		digit;
	int		exp;
	int		counter;
	long	num_long;
	int		minus;

	num_long = (long) n;
	counter = 0;
	minus = 0;
	if (num_long < 0)
	{
		num_long = -num_long;
		write(1, "-", 1);
		minus = 1;
	}
	exp = log_10(num_long);
	while (counter <= exp)
	{
		digit = ((num_long / pow_of(10, exp - counter)) % 10) + 48;
		write(1, &digit, 1);
		counter += 1;
	}
	return (counter + minus);
}

void	write_hex(unsigned long long num, char *base, int *counter)
{
	unsigned int	rem;

	if (num < 1)
	{
		return ;
	}
	rem = num % 16;
	num = num / 16;
	(*counter)++;
	write_hex(num, base, counter);
	write(1, &base[rem], 1);
}
