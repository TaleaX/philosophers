/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdehne <tdehne@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 12:21:20 by tdehne            #+#    #+#             */
/*   Updated: 2022/12/20 10:04:26 by tdehne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static t_bool	can_eat(t_philo_data *philo)
{
	if (philo->data->total_num_philos % 2 == 0)
		return (TRUE);
	if (philo->eating_rot == 1)
		return (printf("philos %d eating rot is 1\n", philo->num), TRUE);
	return (FALSE);
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
			philo->prev_time = get_current_millis();
			output(philo, THINK_STR);
			if (get_current_millis() - philo->prev_time >= philo->data->time_to_eat - 1)
				philo->eating_rot = 1;
			if (!can_eat(philo))
				usleep(200);
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
