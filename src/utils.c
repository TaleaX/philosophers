/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdehne <tdehne@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 12:21:30 by tdehne            #+#    #+#             */
/*   Updated: 2022/12/28 14:06:56 by tdehne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

long long	get_current_millis(void)
{
	t_timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	my_msleep(long long milli_sec, t_data *data)
{
	long long	end;

	end = get_current_millis() + milli_sec;
	while (get_current_millis() < end && is_alive(data))
		usleep(500);
}

int	ft_strncmp(char *s1, char *s2, unsigned int n)
{
	unsigned int	i;
	unsigned char	*d_s1;
	unsigned char	*d_s2;

	d_s1 = (unsigned char *) s1;
	d_s2 = (unsigned char *) s2;
	i = 0;
	while (i < n)
	{
		if (s1[i] != s2[i] || !s1[i])
			return (d_s1[i] - d_s2[i]);
		i++;
	}
	return (0);
}

int	ft_max(int first, int sec)
{
	if (first > sec)
		return (first);
	return (sec);
}

int	ft_min(int first, int sec)
{
	if (first < sec)
		return (first);
	return (sec);
}
