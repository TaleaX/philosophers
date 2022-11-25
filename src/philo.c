#include "../inc/philo.h"

void    *routine(void *content)
{

    t_philo_data philo_data;

    philo_data = *(t_philo_data *)content;
    if (philo_data.total_num_philos > 1)
    {
        while (1)
        {
            printf("philo num %d is thinking\n", philo_data.num);
            pthread_mutex_lock(&philo_data.forks[philo_data.num]);
            pthread_mutex_lock(&philo_data.forks[(philo_data.num + 1) % philo_data.total_num_philos]);
            printf("philo num %d finished thinking\n", philo_data.num);
            gettimeofday(philo_data.time_arr + philo_data.num, NULL);
            do_activity(philo_data, EAT, EAT_STR);
            (*philo_data.rounds)++;
            pthread_mutex_unlock(&philo_data.forks[philo_data.num]);
            pthread_mutex_unlock(&philo_data.forks[(philo_data.num + 1) % philo_data.total_num_philos]);
            do_activity(philo_data, SLEEP, SLEEP_STR);
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
        pthread_mutex_lock(&philo_data.mutex_for_lock);
		i = 0;
        if (philo_data.total_num_philos == 1)
        {
            gettimeofday(&current_time, NULL);
            printf("Philo %d died: Timestap m %d\n", i, current_time.tv_usec);
            return (NULL);
        }
        if (philo_data.min_rounds != -1 && philo_data.min_rounds <= *philo_data.rounds)
        {
            gettimeofday(&current_time, NULL);
            printf("Philos have eaten at leat %d times: Timestamp %d\n", philo_data.min_rounds / philo_data.total_num_philos, current_time.tv_usec);
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
                return (NULL);
			}
			i++;
			pthread_mutex_unlock(&philo_data.mutex_for_lock);
		}
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
        free(philo_data.time_arr);
        free(philo_data.rounds);
    }
    return (EXIT_SUCCESS);
}
