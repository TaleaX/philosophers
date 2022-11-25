#include "../inc/philo.h"

t_bool  is_dead(t_philo_data *philo_data, int num)
{
    t_timeval   current_time;
	double	time_last_meal;
	double	curtime;
	int i;

	i = 0;
	while (i < num)
	{
		pthread_mutex_lock(&philo_data->mutex_for_lock);
		time_last_meal = get_ms(philo_data->time_arr[i]);
		gettimeofday(&current_time, NULL);
		curtime = get_ms(current_time);
		if (curtime - time_last_meal > ((double) philo_data->time_to_die / 1000))
		{
			philo_data->time_death = current_time;
			return (TRUE);
		}
		i++;
		pthread_mutex_unlock(&philo_data->mutex_for_lock);
	}
	//printf("in here philo_data->time_to_die  =  %f > %f \t current %f last meal %f\n", (double) philo_data->time_to_die / 1000, curtime - time_last_meal, curtime, time_last_meal);
    return (FALSE);
}

double	get_ms(t_timeval time)
{
	double	cur;

	cur = 0;
	cur += time.tv_sec;
	cur += (double) time.tv_usec / 1000000.0;
	return (cur);
}



void    do_activity(t_philo_data philo_data, t_activity activity, char *activity_str)
{
    printf("philo num %d starts %s\n", philo_data.num, activity_str);
    if (activity == EAT)
        usleep(philo_data.time_to_eat * 1000);
    else if (activity == SLEEP)
        usleep(philo_data.time_to_sleep * 1000);
    printf("philo num %d finished %s\n", philo_data.num, activity_str);
}
