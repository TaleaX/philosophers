/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdehne <tdehne@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 10:57:17 by tdehne            #+#    #+#             */
/*   Updated: 2022/12/28 14:05:55 by tdehne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	philos_full(t_data *data, int philos_full, int i)
{
	pthread_mutex_lock(&data->philos[i].mutex_times_eaten);
	if (data->min_times_eaten != -1
		&& data->philos[i].times_eaten >= data->min_times_eaten)
		philos_full++;
	pthread_mutex_unlock(&data->philos[i].mutex_times_eaten);
	return (philos_full);
}

t_bool	is_alive(t_data *data)
{
	t_bool	alive;

	pthread_mutex_lock(&data->mutex_alive);
	alive = data->alive;
	pthread_mutex_unlock(&data->mutex_alive);
	return (alive);
}

t_bool	is_dead(t_data *data, int i)
{
	long long	current;
	long long	last_eaten;

	pthread_mutex_lock(&data->philos[i].mutex_last_eaten);
	current = get_current_millis();
	last_eaten = data->philos[i].last_eaten;
	if (last_eaten && (current - last_eaten >= data->time_to_die))
		return (pthread_mutex_unlock(&data->philos[i].mutex_last_eaten), TRUE);
	pthread_mutex_unlock(&data->philos[i].mutex_last_eaten);
	return (FALSE);
}

int	wait_for_death(t_data *data)
{
	int			i;
	int			full;

	while (1)
	{	
		i = 0;
		full = 0;
		if (data->total_num_philos == 1)
			return (my_msleep(data->time_to_die, data), die(data, 0), 1);
		while (i < data->total_num_philos)
		{
			if (is_dead(data, i))
				return (die(data, i), 1);
			full = philos_full(data, full, i);
			if (full == data->total_num_philos)
				return (exit_threads(data), 1);
			i++;
		}
		usleep(100);
	}
	return (0);
}
