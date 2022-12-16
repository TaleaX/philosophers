/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdehne <tdehne@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 12:21:30 by tdehne            #+#    #+#             */
/*   Updated: 2022/12/16 12:21:32 by tdehne           ###   ########.fr       */
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

void	my_usleep(long long milli_sec)
{
	long long	end;

	end = get_current_millis() + milli_sec;
	while (get_current_millis() < end)
		usleep(100);
}

int	ft_min(int num1, int num2)
{
	if (num1 < num2)
		return (num1);
	return (num2);
}

int	ft_max(int num1, int num2)
{
	if (num1 > num2)
		return (num1);
	return (num2);
}
