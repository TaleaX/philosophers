#include "../inc/philo.h"

void    putstr_arg(char *str, long long arg, char c)
{
    while (*str)
    {
        if (*str == '%' && *(str + 1) != '%')
        {
            if (!c)
            {
                while (1)
                {
                    c = (arg % 10) + '0';
                    write(1, &c, 1);
                    arg /= 10;
                    if (!arg)
                        break ;
                }
            }
            else
                write(1, &c, 1);
            str++;
            continue ;
        }
        write(1, str, 1);
        str++;
    }
}

void    *routine(void *content)
{
    t_philo_data	*philo;

    philo = content;
    philo->thread_start = get_current_millis();
    if (philo->data->total_num_philos > 1)
    {
        while (1)
        {
			    output(philo, THINK_STR);

				pthread_mutex_lock(&philo->data->forks[ft_min(philo->num, (philo->num + 1) % philo->data->total_num_philos)]);
				output(philo, FORK_TAKEN);
				pthread_mutex_lock(&philo->data->forks[ft_max(philo->num, (philo->num + 1) % philo->data->total_num_philos)]);
				output(philo, FORK_TAKEN);
                
				pthread_mutex_lock(&philo->data->mutex);
				// printf("philo %d last eaten %lld current %lld diff %lld diff start %d\n", philo->num, philo->last_eaten, get_current_millis(), get_current_millis() - philo->last_eaten,get_current_millis() - philo->thread_start);
                philo->last_eaten = get_current_millis();
				pthread_mutex_unlock(&philo->data->mutex);
				
				output(philo, EAT_STR);
                my_usleep(philo->data->time_to_eat * 1000);



                pthread_mutex_lock(&philo->data->mutex);
                (*philo->data->rounds)++;
                pthread_mutex_unlock(&philo->data->mutex);

				pthread_mutex_unlock(&philo->data->forks[ft_max(philo->num, (philo->num + 1) % philo->data->total_num_philos)]);
				pthread_mutex_unlock(&philo->data->forks[ft_min(philo->num, (philo->num + 1) % philo->data->total_num_philos)]);
		
                output(philo, SLEEP_STR);
                my_usleep(philo->data->time_to_sleep * 1000);
        }
    }
    return (NULL);
}

int main(int argc, char **argv)
{
    t_data    data;
    // int             i;
    
    // if (argc >= 5 && atoi(argv[1]) > 0)
    // {
    //     // init_data(&data, argv, argc);
    //     // i = 0;
    //     // while (i < data.total_num_philos)
    //     // {
	// 	// 	pthread_mutex_lock(&data.mutex);
    //     //     data.philos[i].num = i;
	// 	// 	pthread_mutex_unlock(&data.mutex);
    //     //     pthread_create(&data.philos[i].philo, NULL, &routine, (void *)&data.philos[i]);
    //     //     // usleep(100);
    //     //     i++;

    //     // }
    //     // i = 0;
    //     // while (i < data.total_num_philos)
    //     // {
    //     //     pthread_detach(data.philos[i].philo);
    //     //     i++;
    //     // }
    //     // wait_for_death(&data);
    // }
    return (EXIT_SUCCESS);
}
