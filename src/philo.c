#include "../inc/philo.h"

pthread_mutex_t mutex_think;
pthread_mutex_t mutex;
pthread_mutex_t mutex_eat;
pthread_mutex_t mutex_sleep;

void    putstr_arg(char *str, int arg, char c, pthread_mutex_t *mutex)
{
    pthread_mutex_lock(mutex);
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
    pthread_mutex_unlock(mutex);
}

void    *routine(void *content)
{

    t_philo_data philo_data;

    philo_data = *(t_philo_data *)content;
    if (philo_data.total_num_philos > 1)
    {
        while (1)
        {
			// pthread_mutex_lock(&mutex_think);
			// ft_putstr_fd("Starts Thinking: Philo ", 1);
			// ft_putnbr_fd(philo_data.num, 1);
			// ft_putstr_fd("\n", 1);
            putstr_arg("Philo % starts thinking \n", philo_data.num, '\0', philo_data.mutex);
			//ft_printf("Philo %d starts thinking \n", philo_data.num);
			// pthread_mutex_unlock(&mutex_think);
            pthread_mutex_lock(&philo_data.forks[philo_data.num]);
            pthread_mutex_lock(&philo_data.forks[(philo_data.num + 1) % philo_data.total_num_philos]);
            putstr_arg("Philo % finishes thinking \n", philo_data.num, '\0', philo_data.mutex);
            // usleep(100);
            // ft_putstr_fd("Finishes Thinking: Philo ", 1);
			// ft_putnbr_fd(philo_data.num, 1);
			// ft_putstr_fd("\n", 1);
            gettimeofday(philo_data.time_arr + philo_data.num, NULL);
            // pthread_mutex_lock(&mutex_eat);
            do_activity(&philo_data, EAT, EAT_STR);
            // pthread_mutex_unlock(&mutex_eat);
            (*philo_data.rounds)++;
            pthread_mutex_unlock(&philo_data.forks[philo_data.num]);
            pthread_mutex_unlock(&philo_data.forks[(philo_data.num + 1) % philo_data.total_num_philos]);
            // pthread_mutex_lock(&mutex_sleep);
            do_activity(&philo_data, SLEEP, SLEEP_STR);
            // pthread_mutex_unlock(&mutex_sleep);
        }
    }
    return (NULL);
}

void	*die(void *content)
{
	t_philo_data    philo_data;
    t_timeval       current_time;
	double          time_last_meal;
	double          curtime;
    int             i;

    philo_data = *(t_philo_data *)content;
	while (1)
	{
        // pthread_mutex_lock(philo_data.mutex_for_lock);
		i = 0;
        if (philo_data.total_num_philos == 1)
        {
            gettimeofday(&current_time, NULL);
            printf("Philo %d died: Timestap m %d\n", i, current_time.tv_usec);
			// pthread_mutex_unlock(philo_data.mutex_for_lock);
            return (NULL);
        }
        if (philo_data.min_rounds != -1 && philo_data.min_rounds <= *philo_data.rounds)
        {
            gettimeofday(&current_time, NULL);
            printf("Philos have eaten at leat %d times: Timestamp %d\n", philo_data.min_rounds / philo_data.total_num_philos, current_time.tv_usec);
			// pthread_mutex_unlock(philo_data.mutex_for_lock);
            return (NULL);
        }
		while (i < philo_data.total_num_philos)
		{
			time_last_meal = get_ms(philo_data.time_arr[i]);
			gettimeofday(&current_time, NULL);
			curtime = get_ms(current_time);
			if (curtime - time_last_meal > ((double) philo_data.time_to_die / 1000))
			{
				philo_data.time_death = current_time;
				printf("Philo %d died: Timestap m %d\n", i, philo_data.time_death.tv_usec);
				// pthread_mutex_unlock(philo_data.mutex_for_lock);
                return (NULL);
			}
			i++;
		}
		// pthread_mutex_unlock(philo_data.mutex_for_lock);
	}
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
        pthread_mutex_init(&mutex_think, NULL);
        pthread_mutex_init(&mutex_sleep, NULL);
        pthread_mutex_init(&mutex_eat, NULL);
        pthread_mutex_init(&mutex, NULL);
		philos = init_philos(atoi(argv[1]));
        init_philo_data(&philo_data, argv, argc);
		//pthread_create(&check_death, NULL, &die, (void *)&philo_data);
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
            pthread_join(philos[i], NULL);
            i++;
        }
		//pthread_join(check_death, NULL);
        free(philo_data.forks);
        free(philo_data.time_arr);
        free(philo_data.rounds);
    }
    return (EXIT_SUCCESS);
}
