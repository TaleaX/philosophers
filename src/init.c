/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdehne <tdehne@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 12:21:11 by tdehne            #+#    #+#             */
/*   Updated: 2022/12/21 13:19:09 by tdehne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static pthread_mutex_t	*create_forks(int num)
{
	pthread_mutex_t	*forks;
	int				i;

	forks = malloc(sizeof(pthread_mutex_t) * (num));
	if (!forks)
		return (NULL);
	i = 0;
	while (i < num)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	return (forks);
}

static t_philo_data	*init_philo_data(int len, t_data *data)
{
	t_philo_data	*philo_data;
	int				i;

	philo_data = malloc(sizeof(t_philo_data) * len);
	if (!philo_data)
		return (NULL);
	i = 0;
	while (i < len)
	{
		philo_data[i].thread_start = get_current_millis();
		philo_data[i].last_eaten = 0;
		philo_data[i].data = data;
		philo_data[i].num = i;
		// philo_data[i].first_fork = get_forks_i(i, len, TRUE);
		// philo_data[i].sec_fork = get_forks_i(i, len, FALSE);
		philo_data[i].first_fork = (i == len - 1) ? ((i + 1) % len) : i;
		philo_data[i].sec_fork = (i == len - 1) ? i : ((i + 1) % len);
		// philo_data[i].first_fork = i;
		// philo_data[i].sec_fork = ((i + 1) % len);
		philo_data[i].times_eaten = 0;
		philo_data[i].rotate_count = (i % 2 == 0) ? data->total_num_philos - i - 1 : data->total_num_philos - i - 2;

		pthread_mutex_init(&philo_data[i].mutex_last_eaten, NULL);
		pthread_mutex_init(&philo_data[i].mutex_times_eaten, NULL);
		i++;
	}
	return (philo_data);
}

void	init_data(t_data *data, char **argv, int argc)
{
	data->total_num_philos = atoi(argv[1]);
	data->time_to_die = atoi(argv[2]);
	data->time_to_eat = atoi(argv[3]);
	data->time_to_sleep = atoi(argv[4]);
	data->alive = TRUE;
	data->threads_start = FALSE;
	data->forks = create_forks(atoi(argv[1]));
	pthread_mutex_init(&data->mutex_write, NULL);
	pthread_mutex_init(&data->mutex_alive, NULL);
	data->min_times_eaten = -1;
	if (argc > 5)
		data->min_times_eaten = atoi(argv[5]);
	data->philos = init_philo_data(data->total_num_philos, data);
}

void	init_routine(t_philo_data *philo)
{
	pthread_mutex_lock(&philo->mutex_last_eaten);
	philo->last_eaten = get_current_millis();
	pthread_mutex_unlock(&philo->mutex_last_eaten);
	if (philo->data->total_num_philos > 1)
		output(philo, THINK_STR);
	if (philo->num % 2 != 0)
		my_msleep(philo->data->time_to_eat);
}

t_bool	check_input(char **argv, int argc)
{
	if (argc < 5 || argc > 6)
		return (FALSE);
	while (--argc > 0)
	{
		if (ft_atoi(argv[argc]) == GT_MAX_INT)
			return (FALSE);
	}
	return (TRUE);
}
