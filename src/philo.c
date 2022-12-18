/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdehne <tdehne@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 12:21:20 by tdehne            #+#    #+#             */
/*   Updated: 2022/12/16 12:41:57 by tdehne           ###   ########.fr       */
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

static long long	time_last_eaten(t_data *data, int i)
{
	long long	last_eaten;

	pthread_mutex_lock(&data->mutex_last_eaten);
	last_eaten = data->philos[i].last_eaten;
	pthread_mutex_unlock(&data->mutex_last_eaten);
	return (last_eaten);
}

int	wait_for_death(t_data *data)
{
	long long	current;
	long long	last_eaten;
	int			i;
	int			full;

	while (1)
	{	
		i = 0;
		full = 0;
		usleep(100);
		if (data->total_num_philos == 1)
			return (die(data, 0), EXIT_SUCCESS);
		while (i < data->total_num_philos)
		{
			pthread_mutex_lock(&data->philos[i].mutex_eat);
			full = philos_full(data, full, i);
			last_eaten = time_last_eaten(data, i);
			current = get_current_millis();
			pthread_mutex_unlock(&data->philos[i].mutex_eat);
			if (last_eaten && (current - last_eaten > data->time_to_die))
				return (die(data, i), EXIT_SUCCESS);
			if (full == data->total_num_philos)
				return (exit_threads(data), EXIT_SUCCESS);
			i++;
		}
	}
	return (EXIT_FAILURE);
}

void	*routine(void *content)
{
	t_philo_data	*philo;

	philo = content;
	init_routine(philo);
	if (philo->data->total_num_philos > 1)
	{
		while (is_alive(philo->data))
		{
			output(philo, THINK_STR);
			philo_eat(philo);
			philo_sleep(philo);
		}
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		i;

	if (ft_atoi(argv[1]) <= 0)
		printf("The number of Philos you entered is 0 or smaller, try again\n");
	else if (check_input(argv, argc))
	{
		init_data(&data, argv, argc);
		i = 0;
		while (i < data.total_num_philos)
		{
			pthread_create(&data.philos[i].philo, NULL, &routine, \
				(void *)&data.philos[i]);
			i++;
		}
		wait_for_death(&data);
		my_exit(&data);
	}
	else
		printf("Args: number_of_philosophers time_to_die time_to_eat" \
			"time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
	return (EXIT_SUCCESS);
}
