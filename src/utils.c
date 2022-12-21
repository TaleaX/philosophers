/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdehne <tdehne@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 12:21:30 by tdehne            #+#    #+#             */
/*   Updated: 2022/12/21 13:06:23 by tdehne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

long long	get_current_millis(void)
{
	t_timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

t_bool	is_alive(t_data *data)
{
	t_bool	alive;

	pthread_mutex_lock(&data->mutex_alive);
	alive = data->alive;
	pthread_mutex_unlock(&data->mutex_alive);
	return (alive);
}

void	my_msleep(long long milli_sec)
{
	long long	end;

	end = get_current_millis() + milli_sec;
	while (get_current_millis() < end)
		usleep(500);
}

int	get_forks_i(int philo_num, int total_philos, t_bool first_fork)
{
	if (first_fork)
	{
		if (philo_num % 2 == 0)
			return (philo_num);
		else
			return ((philo_num + 1) % total_philos);
	}
	if (philo_num % 2 == 0)
		return ((philo_num + 1) % total_philos);
	return (philo_num);
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
