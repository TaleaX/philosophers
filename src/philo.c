/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdehne <tdehne@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 12:21:20 by tdehne            #+#    #+#             */
/*   Updated: 2022/12/28 14:04:59 by tdehne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

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
			if (philo->data->total_num_philos % 2 != 0
				&& philo->rotate_count == 0)
			{
				my_msleep(philo->data->time_to_eat, philo->data);
				philo->rotate_count = philo->data->total_num_philos - 1;
			}
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

	if (argv[1] && ft_atoi(argv[1]) <= 0)
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
		data.threads_start = TRUE;
		wait_for_death(&data);
		my_exit(&data);
	}
	else
		printf("Args: number_of_philosophers time_to_die time_to_eat" \
			"time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
	return (EXIT_SUCCESS);
}
