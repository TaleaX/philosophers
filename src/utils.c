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



void    do_activity(t_philo_data *philo_data, t_activity activity, char *activity_str)
{
	pthread_mutex_lock(philo_data->mutex_for_lock);
    ft_printf("philo num %d starts %s\n", philo_data->num, activity_str);
	// ft_putstr_fd("Philo num ", 1);
	// ft_putnbr_fd(philo_data->num, 1);
	// ft_putstr_fd(" starts ", 1);
	// ft_putstr_fd(activity_str, 1);
	// ft_putstr_fd("\n", 1);
	pthread_mutex_unlock(philo_data->mutex_for_lock);
    if (activity == EAT)
        usleep(philo_data->time_to_eat * 1000);
    else if (activity == SLEEP)
        usleep(philo_data->time_to_sleep * 1000);
	pthread_mutex_lock(philo_data->mutex_for_lock);
	// ft_putstr_fd("Philo num ", 1);
	// ft_putnbr_fd(philo_data->num, 1);
	// ft_putstr_fd(" finished ", 1);
	// ft_putstr_fd(activity_str, 1);
	// ft_putstr_fd("\n", 1);
    ft_printf("philo num %d finished %s\n", philo_data->num, activity_str);
	pthread_mutex_unlock(philo_data->mutex_for_lock);
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
        //printf("end time %f, wait usec %f\n", end_time_usec, wait_usec);
        gettimeofday(&start_sleep, NULL);
        unix_time_usec = get_ms(start_sleep);
        if (unix_time_usec >= end_time_usec)
            break ;
    }
}