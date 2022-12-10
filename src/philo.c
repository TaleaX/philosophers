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
    t_data	data;

    data = *(t_data *)content;
    data.philos[data.philos->num].thread_start = get_current_millis();
    if (data.total_num_philos > 1)
    {
        while (1)
        {
			    output(&data, THINK_STR);
				if (data.num == data.total_num_philos - 1)
					lock_right_fork(&data);
				else
                	pthread_mutex_lock(&data.forks[data.num]);
				output(&data, FORK_TAKEN);
				if (data.num == data.total_num_philos - 1)
					pthread_mutex_lock(&data.forks[data.num]);
				else
					lock_right_fork(&data);
				output(&data, FORK_TAKEN);
				pthread_mutex_lock(data.mutex);
                data.time_last_eaten[data.num] = get_current_millis();
				pthread_mutex_unlock(data.mutex);
                output(&data, EAT_STR);
                my_usleep(data.time_to_eat * 1000);
                pthread_mutex_lock(data.mutex);
                (*data.rounds)++;
                pthread_mutex_unlock(data.mutex);

				if (data.num == data.total_num_philos - 1)
					unlock_right_fork(&data);
				else
                	pthread_mutex_unlock(&data.forks[data.num]);
				if (data.num == data.total_num_philos - 1)
					pthread_mutex_unlock(&data.forks[data.num]);
				else
					unlock_right_fork(&data);
                output(&data, SLEEP_STR);
                my_usleep(data.time_to_sleep * 1000);
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
			pthread_mutex_lock(&data.mutex);
            data.philos[i].num = i;
            pthread_create(&data.philos[i], NULL, &routine, (void *)&data);
            // my_usleep(100);
            i++;

        }
        i = 0;
        while (i < data.total_num_philos)
        {
            pthread_detach(&data.philos[i]);
            i++;
        }
        wait_for_death(&data);
        free(data.rounds);
    }
    return (EXIT_SUCCESS);
}
