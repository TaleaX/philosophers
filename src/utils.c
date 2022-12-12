#include "../inc/philo.h"

void	wait_for_death(t_data *data)
{
	long long          current;
    long long          time_last_eaten;
    int             i;

	while (1)
	{
		pthread_mutex_lock(&data->mutex);
		i = 0;
        if (data->total_num_philos == 1)
        {
            current = get_current_millis();
            printf("Philo %d died: Timestap m %d\n", i, get_mils_start(current, data->philos->thread_start));
			// pthread_mutex_unlock(&data->mutex);
            return ;
        }
        if (data->min_rounds != -1 && data->min_rounds <= *data->rounds)
        {
            current = get_current_millis();
            printf("Philos have eaten at least %d times\n", (int)(data->min_rounds / data->total_num_philos));
			pthread_mutex_unlock(&data->mutex);
            return ;
        }
		while (i < data->total_num_philos)
		{
            current = get_current_millis();
            time_last_eaten = data->philos[i].last_eaten;
			if (time_last_eaten && (current - time_last_eaten > data->time_to_die))
			{
				printf("Philo %d time last eaten %lld current %lld diff %lld\n", i, time_last_eaten, current, current - time_last_eaten);
				printf("-----------------------------Tmstp %d Philo %d died\n", get_mils_start(current, data->philos[i].thread_start), i);
				pthread_mutex_unlock(&data->mutex);
                return ;
			}
			i++;
		}
		pthread_mutex_unlock(&data->mutex);
	}
}

// void	lock_right_fork(t_philo_data *philo_data)
// {
// 	int				last_index;

// 	pthread_mutex_lock(philo_data->mutex);
// 	last_index = (philo_data->num + 1) % philo_data->total_num_philos;
// 	pthread_mutex_unlock(philo_data->mutex);
// 	pthread_mutex_lock(&philo_data->forks[last_index]);
// }

// void	unlock_right_fork(t_philo_data *philo_data)
// {
// 	int				last_index;

// 	pthread_mutex_lock(philo_data->mutex);
// 	last_index = (philo_data->num + 1) % philo_data->total_num_philos;
// 	pthread_mutex_unlock(philo_data->mutex);
// 	pthread_mutex_unlock(&philo_data->forks[last_index]);
// }


// void	set_var(t_philo_data *philo_data, int *dest, int source)
// {
// 	pthread_mutex_lock(philo_data->mutex);
//     (*dest) = source;
// 	pthread_mutex_unlock(philo_data->mutex);
// }

// void	take_fork_print(t_philo_data *philo_data)
// {
// 	long long		current;

// 	pthread_mutex_lock(philo_data->mutex);
// 	current = get_current_millis();
// 	printf("%d %d has taken a fork\n", get_mils_start(current, philo_data->time_thread_start[philo_data->num]), philo_data->num);
// 	pthread_mutex_unlock(philo_data->mutex);
// }

double	get_s(t_timeval time)
{
	double	cur;

	cur = 0;
	cur += time.tv_sec;
	cur += (double) time.tv_usec / 1e6;
	return (cur);
}

long long	get_current_millis()
{
    t_timeval time;
	long long	cur;

    gettimeofday(&time, NULL);
	cur = 0;
	cur += time.tv_sec * 1000;
	cur += (long long) time.tv_usec / 1000;
	return (cur);
}

int	get_mils_start(long long current, long long start)
{
	return (current - start);
}

void	output(t_philo_data *philo, char *activity_str)
{
	long long   current;

	pthread_mutex_lock(&philo->data->mutex_write);
	current = get_current_millis();
    printf("%d %d %s \n", (int)(current - philo->thread_start), philo->num, activity_str);
	pthread_mutex_unlock(&philo->data->mutex_write);
}

int	ft_min(int num1, int num2)
{
	return ((num1 < num2 ? num1 : num2));
}

int	ft_max(int num1, int num2)
{
	return ((num1 > num2 ? num1 : num2));
}

void    my_usleep(double wait_usec)
{
    t_timeval   start_sleep;
    double      unix_time_usec;
    double      end_time_usec;

    gettimeofday(&start_sleep, NULL);
    end_time_usec = get_s(start_sleep) + (wait_usec / 1000000.0);
    while (1)
    {
        gettimeofday(&start_sleep, NULL);
        unix_time_usec = get_s(start_sleep);
        if (unix_time_usec >= end_time_usec)
            break ;
    }
}

// void	my_sleep(size_t sleep)
// {
// 	time_t	t;

// 	t = get_time() + sleep;
// 	while (get_time() < t)
// 		usleep(30);
// }