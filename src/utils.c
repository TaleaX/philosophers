#include "../inc/philo.h"

// t_bool  is_dead(t_philo_data *philo_data, int num)
// {
//     t_timeval   current_time;
// 	double	time_last_meal;
// 	double	curtime;
// 	int i;

// 	i = 0;
// 	while (i < num)
// 	{
// 		pthread_mutex_lock(&philo_data->mutex_for_lock);
// 		time_last_meal = get_ms(philo_data->time_arr[i]);
// 		gettimeofday(&current_time, NULL);
// 		curtime = get_ms(current_time);
//         printf("philo %d, cur time - last meal %f, time to die %f\n", num , curtime - time_last_meal, (double) philo_data->time_to_die / 1000.0);
// 		if (curtime - time_last_meal > ((double) philo_data->time_to_die / 1000.0))
// 		{
// 			philo_data->time_death = current_time;
// 			return (TRUE);
// 		}
// 		i++;
// 		pthread_mutex_unlock(&philo_data->mutex_for_lock);
// 	}
//     return (FALSE);
// }

double	get_ms(t_timeval time)
{
	double	cur;

	cur = 0;
	cur += time.tv_sec;
	cur += (double) time.tv_usec / 1000000.0;
	return (cur);
}

long long	get_millis(t_timeval time)
{
	long long	cur;

	cur = 0;
	cur += time.tv_sec * 1000;
	cur += (long long) time.tv_usec / 1000.0;
	return (cur);
}

void	output(t_philo_data *philo_data, char *activity_str)
{
	t_timeval	current;

	pthread_mutex_lock(philo_data->mutex);
	gettimeofday(&current, NULL);
	// putstr_arg("% ", get_millis(current), 0);
	// putstr_arg("% is ", philo_data->num, 0);
    // putstr_arg(activity_str, 0, 0);
	// putstr_arg("\n", 0, 0);
	printf("%lld %d is %s\n", get_millis(current), philo_data->num, activity_str);
	pthread_mutex_unlock(philo_data->mutex);
}

void    my_usleep(double wait_usec)
{
    t_timeval   start_sleep;
    double      unix_time_usec;
    double      end_time_usec;

    gettimeofday(&start_sleep, NULL);
    end_time_usec = get_ms(start_sleep) + (wait_usec / 1000000.0);
    while (1)
    {
        gettimeofday(&start_sleep, NULL);
        unix_time_usec = get_ms(start_sleep);
        if (unix_time_usec >= end_time_usec)
            break ;
    }
}