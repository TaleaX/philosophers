/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdehne <tdehne@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 09:16:58 by tdehne            #+#    #+#             */
/*   Updated: 2022/12/13 11:12:19 by tdehne           ###   ########.fr       */
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
        if (data->total_num_philos == 1)
        {
			data->alive = FALSE;
            current = get_current_millis();
			pthread_mutex_lock(&data->mutex_write);
            printf("Philo %d died: Timestap m %d\n", i, get_diff_start(current, data->philos->thread_start));
			pthread_mutex_unlock(&data->mutex_write);
            return ;
        }
        // if (data->min_rounds != -1 && data->min_rounds <= *data->rounds)
        // {
        //     current = get_current_millis();
        //     printf("Philos have eaten at least %d times\n", (int)(data->min_rounds / data->total_num_philos));
		// 	pthread_mutex_unlock(&data->mutex);
        //     return ;
        // }
		while (i < data->total_num_philos)
		{
            current = get_current_millis();
			pthread_mutex_lock(&data->mutex);
            time_last_eaten = data->philos[i].last_eaten;
			pthread_mutex_unlock(&data->mutex);
			if (time_last_eaten && (current - time_last_eaten > data->time_to_die))
			{
				data->alive = FALSE;
				pthread_mutex_lock(&data->mutex);
				printf("Philo %d time last eaten %lld current %lld diff %lld\n", i, time_last_eaten, current, current - time_last_eaten);
				// printf("-----------------------------Tmstp %d Philo %d died\n", get_diff_start(current, data->philos[i].thread_start), i);
				pthread_mutex_unlock(&data->mutex);
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
    philo->thread_start = get_current_millis();
    if (philo->data->total_num_philos > 1)
    {
        while (philo->data->alive)
        {
			    output(philo, THINK_STR);

				pthread_mutex_lock(&philo->data->forks[ft_min(philo->num, (philo->num + 1) % philo->data->total_num_philos)]);
				output(philo, FORK_TAKEN);
				pthread_mutex_lock(&philo->data->forks[ft_max(philo->num, (philo->num + 1) % philo->data->total_num_philos)]);
				output(philo, FORK_TAKEN);
                
				pthread_mutex_lock(&philo->data->mutex);
				// printf("philo %d last eaten %lld current %lld diff %lld diff start %d\n", philo->num, philo->last_eaten, get_current_millis(), get_current_millis() - philo->last_eaten,get_current_millis() - philo->thread_start);
                if (philo->data->alive)
					philo->last_eaten = get_current_millis();
				pthread_mutex_unlock(&philo->data->mutex);
				
				output(philo, EAT_STR);
                my_usleep(philo->data->time_to_eat);



                pthread_mutex_lock(&philo->data->mutex);
                (*philo->data->rounds)++;
                pthread_mutex_unlock(&philo->data->mutex);

				pthread_mutex_unlock(&philo->data->forks[ft_max(philo->num, (philo->num + 1) % philo->data->total_num_philos)]);
				pthread_mutex_unlock(&philo->data->forks[ft_min(philo->num, (philo->num + 1) % philo->data->total_num_philos)]);
		
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
        init_data(&data, argv, argc);
        i = 0;
        while (i < data.total_num_philos)
        {
            pthread_create(&data.philos[i].philo, NULL, &routine, (void *)&data.philos[i]);
            i++;
        }
        i = 0;
        wait_for_death(&data);
        while (i < data.total_num_philos)
        {
            pthread_join(data.philos[i].philo, NULL);
            i++;
        }
    }
    return (EXIT_SUCCESS);
}
