/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdehne <tdehne@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 09:17:34 by tdehne            #+#    #+#             */
/*   Updated: 2022/12/14 14:34:05 by tdehne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

long long	get_current_millis()
{
    t_timeval time;

    gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	get_diff_start(long long current, long long start)
{
	return (current - start);
}

t_bool	is_alive(t_data *data)
{
	t_bool	alive;

	pthread_mutex_lock(&data->mutex_alive);
	alive = data->alive;
	pthread_mutex_unlock(&data->mutex_alive);
	return (alive);
}

void	output(t_philo_data *philo, char *activity_str)
{
	long long   current;

	pthread_mutex_lock(&philo->data->mutex_write);
	if (is_alive(philo->data) || !strncmp(activity_str, DEAD, 5))
	{
		current = get_current_millis();
		printf("%dms %d %s \n", (int)(current - philo->thread_start), philo->num, activity_str);
	}
	pthread_mutex_unlock(&philo->data->mutex_write);
}

void    my_usleep(long long milli_sec)
{
	long long end = get_current_millis() + milli_sec;

	while (get_current_millis() < end)
		usleep(500);
}

int	ft_min(int num1, int num2)
{
	return ((num1 < num2 ? num1 : num2));
}

int	ft_max(int num1, int num2)
{
	return ((num1 > num2 ? num1 : num2));
}

void	exit_threads(t_data *data)
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