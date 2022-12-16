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

void	wait_for_death(t_data *data)
{
	long long          	current;
    long long          	time_last_eaten;
    int					i;
	int					full;

	while (1)
	{	
		i = 0;
		full = 0;
		usleep(100);
        if (data->total_num_philos == 1)
        {
			pthread_mutex_lock(&data->mutex_alive);
			data->alive = FALSE;
			pthread_mutex_unlock(&data->mutex_alive);
            current = get_current_millis();
			output(&data->philos[0], DEAD);
            return ;
        }
		while (i < data->total_num_philos)
		{
			pthread_mutex_lock(&data->mutex_times_eaten);
			if (data->min_times_eaten != -1 && data->philos[i].times_eaten >= data->min_times_eaten)
				full++;
			pthread_mutex_unlock(&data->mutex_times_eaten);
            current = get_current_millis();
			pthread_mutex_lock(&data->mutex_last_eaten);
            time_last_eaten = data->philos[i].last_eaten;
			pthread_mutex_unlock(&data->mutex_last_eaten);
			if (time_last_eaten && (current - time_last_eaten > data->time_to_die))
			{
				pthread_mutex_lock(&data->mutex_alive);
				data->alive = FALSE;
				pthread_mutex_unlock(&data->mutex_alive);
				output(&data->philos[i], DEAD);
                return ;
			}
			if (full == data->total_num_philos)
			{
				pthread_mutex_lock(&data->mutex_alive);
				data->alive = FALSE;
				pthread_mutex_unlock(&data->mutex_alive);
                return ;
			}
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
        exit_threads(&data);
    }
    return (EXIT_SUCCESS);
}
