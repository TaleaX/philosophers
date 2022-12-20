/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdehne <tdehne@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 10:57:17 by tdehne            #+#    #+#             */
/*   Updated: 2022/12/20 11:37:55 by tdehne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	philos_full(t_data *data, int philos_full, int i)
{
	pthread_mutex_lock(&data->mutex_times_eaten);
	if (data->min_times_eaten != -1
		&& data->philos[i].times_eaten >= data->min_times_eaten)
		philos_full++;
	pthread_mutex_unlock(&data->mutex_times_eaten);
	return (philos_full);
}

static t_bool	is_dead(t_data *data, int i)
{
	long long	current;
	long long	last_eaten;

	pthread_mutex_lock(&data->mutex_last_eaten);
	last_eaten = data->philos[i].last_eaten;
	pthread_mutex_unlock(&data->mutex_last_eaten);
	current = get_current_millis();
	if (last_eaten && (current - last_eaten >= data->time_to_die))
		return (TRUE);
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
		usleep(100);
		if (data->total_num_philos == 1)
			return (my_usleep(data->time_to_die), die(data, 0), EXIT_SUCCESS);
		while (i < data->total_num_philos)
		{
			if (is_dead(data, i))
				return (die(data, i), EXIT_SUCCESS);
			full = philos_full(data, full, i);
			if (full == data->total_num_philos)
				return (exit_threads(data), EXIT_SUCCESS);
			i++;
		}
	}
	return (EXIT_FAILURE);
}
