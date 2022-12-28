/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activities.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdehne <tdehne@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 12:20:42 by tdehne            #+#    #+#             */
/*   Updated: 2022/12/28 14:05:41 by tdehne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	philo_eat(t_philo_data *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->first_fork]);
	output(philo, FORK_TAKEN);
	pthread_mutex_lock(&philo->data->forks[philo->sec_fork]);
	output(philo, FORK_TAKEN);
	{
		pthread_mutex_lock(&philo->mutex_last_eaten);
		philo->last_eaten = get_current_millis();
		pthread_mutex_unlock(&philo->mutex_last_eaten);
		output(philo, EAT_STR);
		my_msleep(philo->data->time_to_eat, philo->data);
		philo->rotate_count--;
		pthread_mutex_lock(&philo->mutex_times_eaten);
		philo->times_eaten++;
		pthread_mutex_unlock(&philo->mutex_times_eaten);
	}
	pthread_mutex_unlock(&philo->data->forks[philo->sec_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->first_fork]);
}

void	philo_sleep(t_philo_data *philo)
{
	output(philo, SLEEP_STR);
	my_msleep(philo->data->time_to_sleep, philo->data);
	philo->rotate_count--;
}

void	output(t_philo_data *philo, char *activity_str)
{
	long long	current;

	pthread_mutex_lock(&philo->data->mutex_write);
	if (is_alive(philo->data) || !ft_strncmp(activity_str, DEAD, 5))
	{
		current = get_current_millis();
		printf("%d %d %s\n", (int)(current - philo->thread_start), \
				philo->num + 1, activity_str);
	}
	pthread_mutex_unlock(&philo->data->mutex_write);
}
