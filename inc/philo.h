/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdehne <tdehne@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 12:22:22 by tdehne            #+#    #+#             */
/*   Updated: 2022/12/16 12:22:24 by tdehne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <string.h>
# include <sys/time.h>

# define TRUE 1
# define FALSE 0
# define EAT_STR "is eating \U0001F35B"
# define SLEEP_STR "is sleeping \U0001F4A4"
# define THINK_STR "is thinking \U0001F4AD"
# define FORK_TAKEN "has taken a fork \U0001F962"
# define DEAD "died"
# define GT_MAX_INT 2147483648

typedef struct timeval	t_timeval;
typedef int				t_bool;

typedef enum activity {
	EAT,
	SLEEP,
	THINK
}	t_activity;

typedef struct s_philo_data {
	int				num;
	pthread_t		philo;
	long long		thread_start;
	long long		last_eaten;
	int				first_fork;
	int				sec_fork;
	int				times_eaten;
	pthread_mutex_t	mutex_eat;
	struct s_data	*data;
}	t_philo_data;

typedef struct s_data {
	int				total_num_philos;
	int				min_times_eaten;
	t_bool			alive;
	pthread_mutex_t	*forks;
	pthread_mutex_t	mutex_times_eaten;
	pthread_mutex_t	mutex_alive;
	pthread_mutex_t	mutex_write;
	pthread_mutex_t	mutex_last_eaten;
	int				time_to_sleep;
	int				time_to_die;
	int				time_to_eat;
	t_philo_data	*philos;
}	t_data;

//utils
t_bool		is_dead(t_philo_data *philo_data, int num);
void		my_usleep(long long milli_sec);
long long	get_current_millis(void);
int			get_forks_i(int philo_num, int total_philos, t_bool first_fork);
t_bool		is_alive(t_data *data);
void		init_routine(t_philo_data *philo);
int			ft_strncmp(char *s1, char *s2, unsigned int n);

//end
void		exit_threads(t_data *data);
void		my_exit(t_data *data);
// void		wait_for_death(t_data *data);
void		die(t_data *data, int i);

//activites
void		philo_sleep(t_philo_data *philo);
void		output(t_philo_data *philo, char *activity_str);
void		philo_eat(t_philo_data *philo);

//init
void		init_data(t_data *data, char **argv, int argc);
long long	*create_time_arr(int num);
pthread_t	*init_philos(int num);
t_bool		check_input(char **argv, int argc);

//ft_atoi
long long	ft_atoi(const char *nptr);

#endif