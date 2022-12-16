/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdehne <tdehne@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 12:20:53 by tdehne            #+#    #+#             */
/*   Updated: 2022/12/16 12:20:56 by tdehne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	my_exit(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->total_num_philos)
	{
		pthread_join(data->philos[i].philo, NULL);
		i++;
	}
	i = 0;
	while (i < data->total_num_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->mutex_times_eaten);
	pthread_mutex_destroy(&data->mutex_last_eaten);
	pthread_mutex_destroy(&data->mutex_alive);
	pthread_mutex_destroy(&data->mutex_write);
	free(data->forks);
	free(data->philos);
}

void	exit_threads(t_data *data)
{
	pthread_mutex_lock(&data->mutex_alive);
	data->alive = FALSE;
	pthread_mutex_unlock(&data->mutex_alive);
}

void	die(t_data *data, int i)
{
	exit_threads(data);
	output(&data->philos[i], DEAD);
}
