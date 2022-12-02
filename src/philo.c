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
	t_timeval		current;

    philo_data = *(t_philo_data *)content;
	pthread_mutex_lock(philo_data.mutex);
	gettimeofday(&current, NULL);
	philo_data.time_thread_start[philo_data.num] = get_millis(current);
	philo_data.time_last_eaten[philo_data.num] = get_millis(current);
	pthread_mutex_unlock(philo_data.mutex);
    if (philo_data.total_num_philos > 1)
    {
        while (1)
        {
			output(&philo_data, THINK_STR);

            pthread_mutex_lock(&philo_data.forks[philo_data.num]);

			pthread_mutex_lock(philo_data.mutex);
			gettimeofday(&current, NULL);
			putstr_arg("% has taken a fork\n", philo_data.num, 0);
			pthread_mutex_unlock(philo_data.mutex);

			pthread_mutex_lock(philo_data.mutex);
			last_index = (philo_data.num + 1) % philo_data.total_num_philos;
            pthread_mutex_lock(&philo_data.forks[last_index]);
			pthread_mutex_unlock(philo_data.mutex);

			pthread_mutex_lock(philo_data.mutex);
			gettimeofday(&current, NULL);
			putstr_arg("% has taken a fork\n", philo_data.num, 0);
			pthread_mutex_unlock(philo_data.mutex);

			pthread_mutex_lock(philo_data.mutex);
            gettimeofday(&current, NULL);
			philo_data.time_last_eaten[philo_data.num] = get_millis(current);
			pthread_mutex_unlock(philo_data.mutex);

            output(&philo_data, EAT_STR);
			my_usleep(philo_data.time_to_eat * 1000);

			pthread_mutex_lock(philo_data.mutex);
            (*philo_data.rounds)++;
			pthread_mutex_unlock(philo_data.mutex);

            pthread_mutex_unlock(&philo_data.forks[philo_data.num]);
			pthread_mutex_lock(philo_data.mutex);
			last_index = (philo_data.num + 1) % philo_data.total_num_philos;
            pthread_mutex_unlock(&philo_data.forks[last_index]);
            pthread_mutex_lock(&philo_data.forks[last_index]);

            output(&philo_data, SLEEP_STR);
			my_usleep(philo_data.time_to_sleep * 1000);
        }
    }
    return (NULL);
}

void	*die(void *content)
{
	t_philo_data    philo_data;
    t_timeval       current_time;
	long long          time_last_meal;
	long long         curtime;
    int             i;
	// int				num;

    philo_data = *(t_philo_data *)content;
	while (1)
	{
		i = 0;
        pthread_mutex_lock(philo_data.mutex);
        if (philo_data.total_num_philos == 1)
        {
            gettimeofday(&current_time, NULL);
            printf("Philo %d died: Timestap m %d\n", i, current_time.tv_usec);
			pthread_mutex_unlock(philo_data.mutex);
            return (NULL);
        }
        if (philo_data.min_rounds != -1 && philo_data.min_rounds <= *philo_data.rounds)
        {
            gettimeofday(&current_time, NULL);
            printf("Philos have eaten at leat %d times: Timestamp %d\n", philo_data.min_rounds / philo_data.total_num_philos, current_time.tv_usec);
			pthread_mutex_unlock(philo_data.mutex);
            return (NULL);
        }
		while (i < philo_data.total_num_philos)
		{
			time_last_meal = philo_data.time_last_eaten[philo_data.num];
			gettimeofday(&current_time, NULL);
			curtime = get_millis(current_time);
			if (curtime - time_last_meal > (philo_data.time_to_die) && time_last_meal != 0)
			{
				printf("curtime %lld timelastmeal %lld dif %lld\n", curtime, time_last_meal, curtime - time_last_meal);
				printf("Philo %d died: Timestap m %lld\n", i, curtime);
				pthread_mutex_unlock(philo_data.mutex);
                return (NULL);
			}
			i++;
		}
		pthread_mutex_unlock(philo_data.mutex);
	}
			exit(0);
	return (NULL);
}

int main(int argc, char **argv)
{
    t_philo_data    philo_data;
    pthread_t       *philos;
	pthread_t		check_death;
    int             i;
    
    if (argc >= 5 && atoi(argv[1]) > 0)
    {
		philos = init_philos(atoi(argv[1]));
        init_philo_data(&philo_data, argv, argc);
		pthread_create(&check_death, NULL, &die, (void *)&philo_data);
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
		pthread_join(check_death, NULL);
        free(philo_data.forks);
        free(philo_data.rounds);
    }
    return (EXIT_SUCCESS);
}
