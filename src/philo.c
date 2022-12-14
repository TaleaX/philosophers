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

	while (1)
	{	
		i = 0;
        // if (data->total_num_philos == 1)
        // {
		// 	data->alive = FALSE;
        //     current = get_current_millis();
		// 	output(&data->philos[0], DEAD);
        //     return ;
        // }
		pthread_mutex_lock(&data->mutex);
		while (i < data->total_num_philos)
		{
            current = get_current_millis();
            time_last_eaten = data->philos[i].last_eaten;
			if (time_last_eaten && (current - time_last_eaten > data->time_to_die))
			{
				data->alive = FALSE;
				output(&data->philos[i], DEAD);
				pthread_mutex_unlock(&data->mutex);
                return ;
			}
			i++;
		}
		pthread_mutex_unlock(&data->mutex);
		
	}
}

void    *routine(void *content)
{
    t_philo_data	*philo;

    philo = content;
    philo->thread_start = get_current_millis();
	pthread_mutex_lock(&philo->data->mutex);
	philo->last_eaten = philo->thread_start;
	pthread_mutex_unlock(&philo->data->mutex);
    if (philo->data->total_num_philos > 1)
    {
		pthread_mutex_lock(&philo->data->mutex);
		if (philo->num % 2)
			usleep(philo->data->time_to_eat);
		pthread_mutex_unlock(&philo->data->mutex);
        while (philo->data->alive)
        {
			output(philo, THINK_STR);
			pthread_mutex_lock(&philo->data->forks[philo->first_fork]);
			output(philo, FORK_TAKEN);
			pthread_mutex_lock(&philo->data->forks[philo->sec_fork]);
			output(philo, FORK_TAKEN);
			
			pthread_mutex_lock(&philo->data->mutex);
			philo->last_eaten = get_current_millis();
			output(philo, EAT_STR);
			pthread_mutex_unlock(&philo->data->mutex);
			my_usleep(philo->data->time_to_eat);

			pthread_mutex_unlock(&philo->data->forks[philo->first_fork]);
			pthread_mutex_unlock(&philo->data->forks[philo->sec_fork]);
	
			output(philo, SLEEP_STR);
			my_usleep(philo->data->time_to_sleep);
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
        init_data(&data, argv);
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
