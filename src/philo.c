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

    t_philo_data	philo_data;
	int				last_index;
	// long long		current;
    // int             start_philo;
    // int             changed_state;

    philo_data = *(t_philo_data *)content;
    pthread_mutex_lock(philo_data.mutex);
    // start_philo = 0;
    // changed_state = 0;
    philo_data.time_thread_start[philo_data.num] = get_current_millis();
    pthread_mutex_unlock(philo_data.mutex);
    if (philo_data.total_num_philos > 1)
    {
        while (1)
        {
			    output(&philo_data, THINK_STR);

				if (philo_data.num == philo_data.total_num_philos - 1)
					lock_right_fork(&philo_data);
				else
                	pthread_mutex_lock(&philo_data.forks[philo_data.num]);
				take_fork_print(&philo_data);
				if (philo_data.num == philo_data.total_num_philos - 1)
					pthread_mutex_lock(&philo_data.forks[philo_data.num]);
				else
					lock_right_fork(&philo_data);
				take_fork_print(&philo_data);
                // pthread_mutex_lock(philo_data.mutex);
                // current = get_current_millis();
                // printf("%d %d has taken a fork\n", get_mils_start(current, philo_data.time_thread_start[philo_data.num]), philo_data.num);
                // last_index = (philo_data.num + 1) % philo_data.total_num_philos;

                // pthread_mutex_unlock(philo_data.mutex);
                // pthread_mutex_lock(&philo_data.forks[last_index]);

                // pthread_mutex_lock(philo_data.mutex);
                // current = get_current_millis();
                // printf("%d %d has taken a fork\n",get_mils_start(current, philo_data.time_thread_start[philo_data.num]), philo_data.num);
                // pthread_mutex_unlock(philo_data.mutex);

				pthread_mutex_lock(philo_data.mutex);
                philo_data.time_last_eaten[philo_data.num] = get_current_millis();
				pthread_mutex_unlock(philo_data.mutex);

                output(&philo_data, EAT_STR);
                my_usleep(philo_data.time_to_eat * 1000);

				// set_var(&philo_data, philo_data.rounds, (*philo_data.rounds) + 1);
                pthread_mutex_lock(philo_data.mutex);
                (*philo_data.rounds)++;
                pthread_mutex_unlock(philo_data.mutex);

				if (philo_data.num == philo_data.total_num_philos - 1)
					unlock_right_fork(&philo_data);
				else
                	pthread_mutex_unlock(&philo_data.forks[philo_data.num]);
				if (philo_data.num == philo_data.total_num_philos - 1)
					pthread_mutex_unlock(&philo_data.forks[philo_data.num]);
				else
					unlock_right_fork(&philo_data);
                // pthread_mutex_unlock(&philo_data.forks[philo_data.num]);
                // pthread_mutex_lock(philo_data.mutex);
                // last_index = (philo_data.num + 1) % philo_data.total_num_philos;
                // pthread_mutex_unlock(philo_data.mutex);
				// // set_var(&philo_data, &last_index, (philo_data.num + 1) % philo_data.total_num_philos);
                // pthread_mutex_unlock(&philo_data.forks[last_index]);

                output(&philo_data, SLEEP_STR);
                my_usleep(philo_data.time_to_sleep * 1000);
        }
    }
    return (NULL);
}

int main(int argc, char **argv)
{
    t_philo_data    philo_data;
    pthread_t       *philos;
    int             i;
    
    if (argc >= 5 && atoi(argv[1]) > 0)
    {
		philos = init_philos(atoi(argv[1]));
        init_philo_data(&philo_data, argv, argc);
        i = 0;
        while (i < philo_data.total_num_philos)
        {
            philo_data.num = i;
            pthread_create(&philos[i], NULL, &routine, (void *)&philo_data);
            my_usleep(100);
            i++;

        }
        i = 0;
        while (i < philo_data.total_num_philos)
        {
            pthread_detach(philos[i]);
            i++;
        }
        wait_for_death(&philo_data);
        free(philo_data.forks);
        free(philo_data.rounds);
		pthread_mutex_unlock(philo_data.mutex);
    }
    return (EXIT_SUCCESS);
}
