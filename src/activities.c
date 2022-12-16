#include "../inc/philo.h"

void	philo_eat(t_philo_data *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->first_fork]);
	output(philo, FORK_TAKEN);
	pthread_mutex_lock(&philo->data->forks[philo->sec_fork]);
	output(philo, FORK_TAKEN);
	
	pthread_mutex_lock(&philo->data->mutex_last_eaten);
	philo->last_eaten = get_current_millis();
	pthread_mutex_unlock(&philo->data->mutex_last_eaten);
	output(philo, EAT_STR);
	my_usleep(philo->data->time_to_eat);

	pthread_mutex_lock(&philo->data->mutex_times_eaten);
	philo->times_eaten++;
	pthread_mutex_unlock(&philo->data->mutex_times_eaten);

	pthread_mutex_unlock(&philo->data->forks[philo->sec_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->first_fork]);
}

void    philo_sleep(t_philo_data *philo)
{
    output(philo, SLEEP_STR);
	my_usleep(philo->data->time_to_sleep);
}

void	output(t_philo_data *philo, char *activity_str)
{
	long long   current;

	pthread_mutex_lock(&philo->data->mutex_write);
	if (is_alive(philo->data) || !strncmp(activity_str, DEAD, 5))
	{
		current = get_current_millis();
		printf("%dms %d %s \n", (int)(current - philo->thread_start), philo->num, activity_str);
	}
	pthread_mutex_unlock(&philo->data->mutex_write);
}
