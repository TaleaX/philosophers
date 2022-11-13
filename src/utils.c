#include "../inc/philo.h"

void    lock(t_bool *mutex, t_philo_data philo_data)
{
    int i = 0;
    while (*mutex == TRUE)
    {
        if (is_dead(philo_data))
            pthread_exit(NULL);
    }
    *mutex = TRUE;
}

void    unlock(t_bool *mutex)
{
    *mutex = FALSE;
}

t_bool  is_dead(t_philo_data philo_data)
{
    t_timeval   current_time;
    t_timeval   time_last_meal;

    pthread_mutex_lock(&philo_data.mutex_for_lock);
    time_last_meal = philo_data.time_arr[philo_data.num];
    gettimeofday(&current_time, NULL);
    pthread_mutex_unlock(&philo_data.mutex_for_lock);
    //printf("current %d last meal %d diff %d\n", current_time.tv_usec, time_last_meal.tv_usec, current_time.tv_usec - time_last_meal.tv_usec);
    if (current_time.tv_usec - time_last_meal.tv_usec > philo_data.time_to_die * 1000)
    {
        pthread_mutex_lock(&philo_data.mutex_for_lock);
        philo_data.time_death = current_time;
        pthread_mutex_unlock(&philo_data.mutex_for_lock);
        return (TRUE);
    }
    return (FALSE);
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