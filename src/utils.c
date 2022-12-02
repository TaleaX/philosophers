#include "../inc/philo.h"

double	get_s(t_timeval time)
{
	double	cur;

	cur = 0;
	cur += time.tv_sec;
	cur += (double) time.tv_usec / 1e6;
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

int	get_mils_start(long long current, long long start)
{
	return (start - current);
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
	printf("%d is %s\n", philo_data->num, activity_str);
	pthread_mutex_unlock(philo_data->mutex);
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