#include "../inc/philo.h"

t_bool  mutex_for_lock = FALSE;
t_bool forks_b[2] = {FALSE, FALSE};

void    *routine(void *content)
{

    t_philo_data philo_data = *(t_philo_data *)content;

    while (1)
    {
        // if (is_dead(&philo_data, philo_data.num))
        // {
        //     printf("Philo %d died: Timestap m %d\n", philo_data.num, philo_data.time_death.tv_usec);
		// 	exit(3);
        // }
        printf("philo num %d is thinking\n", philo_data.num);
        pthread_mutex_lock(&philo_data.forks[philo_data.num]);
        pthread_mutex_lock(&philo_data.forks[(philo_data.num + 1) % philo_data.total_num_philos]);
		// if (is_dead(&philo_data, philo_data.num))
        // {
        //     printf("Philo %d died: Timestap m %d\n", philo_data.num, philo_data.time_death.tv_usec);
		// 	exit(3);
        // }
        printf("philo num %d finished thinking\n", philo_data.num);
        do_activity(philo_data, EAT, EAT_STR);
        gettimeofday(philo_data.time_arr + philo_data.num, NULL);
        pthread_mutex_unlock(&philo_data.forks[philo_data.num]);
        pthread_mutex_unlock(&philo_data.forks[(philo_data.num + 1) % philo_data.total_num_philos]);
        do_activity(philo_data, SLEEP, SLEEP_STR);
    }
    return NULL;
}

void	*die(void *content)
{
	t_philo_data philo_data = *(t_philo_data *)content;
    t_timeval   current_time;
	double	time_last_meal;
	double	curtime;
	int i;
	int	j;

	while (1)
	{
		i = 0;
		printf("curtime well %d \n", philo_data.total_num_philos);
		while (i < philo_data.total_num_philos)
		{
			pthread_mutex_lock(&philo_data.mutex_for_lock);
			time_last_meal = get_ms(philo_data.time_arr[i]);
			gettimeofday(&current_time, NULL);
			curtime = get_ms(current_time);
			printf("curtime %f, last meal %f\n", curtime, time_last_meal);
			if (curtime - time_last_meal > ((double) philo_data.time_to_die / 1000))
			{
				philo_data.time_death = current_time;
				printf("Philo %d died: Timestap m %d\n", i, philo_data.time_death.tv_usec);
				j = 0;
				while (j < philo_data.total_num_philos)
				{
					//pthread_detach(philo_data.philos[j]);
					exit(3);
					j++;
				}
			}
			i++;
			pthread_mutex_unlock(&philo_data.mutex_for_lock);
		}
	}
	return NULL;
	//printf("in here philo_data->time_to_die  =  %f > %f \t current %f last meal %f\n", (double) philo_data->time_to_die / 1000, curtime - time_last_meal, curtime, time_last_meal);
}

int main(int argc, char **argv)
{
    int num_philos = atoi(argv[1]);
    t_philo_data    philo_data;
    pthread_t       *philos;
	pthread_t		check_death;
    int             i;
    
    if (argc >= 5)
    {
		philos = init_philos(atoi(argv[1]));
        init_philo_data(&philo_data, argv, argc);
		philo_data.philos = philos;
        i = 0;
		pthread_create(&check_death, NULL, &die, (void *)&philo_data);
        while (i < num_philos)
        {
            //philo_data.num = malloc(sizeof(int));
            philo_data.num = i;
            pthread_create(&philos[i], NULL, &routine, (void *)&philo_data);
            usleep(100);
            i++;

        }
        i = 0;
        while (i < num_philos)
        {
            pthread_join(philos[i], NULL);
            i++;
        }
		pthread_join(check_death, NULL);
        //pthread_mutex_destroy(&mutex);
    }
    return 0;
}
