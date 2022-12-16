/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdehne <tdehne@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 09:16:58 by tdehne            #+#    #+#             */
/*   Updated: 2022/12/14 14:38:30 by tdehne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	philos_full(t_data *data, int philos_full, int i)
{
	pthread_mutex_lock(&data->mutex_times_eaten);
	if (data->min_times_eaten != -1 && data->philos[i].times_eaten >= data->min_times_eaten)
		philos_full++;
	pthread_mutex_unlock(&data->mutex_times_eaten);
	return (philos_full);
}

static void exit_threads(t_data *data)
{

	pthread_mutex_lock(&data->mutex_alive);
	data->alive = FALSE;
	pthread_mutex_unlock(&data->mutex_alive);
}

static long long	time_last_eaten(t_data *data, int i)
{
	long long          	last_eaten;

	pthread_mutex_lock(&data->mutex_last_eaten);
	last_eaten = data->philos[i].last_eaten;
	pthread_mutex_unlock(&data->mutex_last_eaten);
	return (last_eaten);
}

void	wait_for_death(t_data *data)
{
	long long          	current;
	long long          	last_eaten;
    int					i;
	int					full;

	while (1)
	{	
		i = 0;
		full = 0;
		usleep(100);
        if (data->total_num_philos == 1)
            return (die(data));
		while (i < data->total_num_philos)
		{
			full = philos_full(data, full, i);
			current = get_current_millis();
			last_eaten = time_last_eaten(data, i);
			if (last_eaten && (current - last_eaten > data->time_to_die))
                return (die(data));
			if (full == data->total_num_philos)
                return (exit_threads(data));
			i++;
		}
		
	}
}

void    *routine(void *content)
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

int main(int argc, char **argv)
{
    t_data    data;
    int             i;
    
    if (argc >= 5 && atoi(argv[1]) > 0)
    {
        init_data(&data, argv, argc);
        i = 0;
        while (i < data.total_num_philos)
        {
            pthread_create(&data.philos[i].philo, NULL, &routine, (void *)&data.philos[i]);
            i++;
        }
        wait_for_death(&data);
        my_exit(&data);
    }
    return (EXIT_SUCCESS);
}
