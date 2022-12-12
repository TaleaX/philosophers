#ifndef PHILO_H
# define PHILO_H

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>

#define TRUE 1
#define FALSE 0
#define EAT_STR "is eating"
#define SLEEP_STR "is sleeping"
#define THINK_STR "is thinking"
#define FORK_TAKEN "has taken a fork"
#define GET_MAX ft_max(philo->num, (philo->num + 1) % philo->data->total_num_philos)
#define GET_MIN ft_max(philo->num, (philo->num + 1) % philo->data->total_num_philos)

typedef struct timeval t_timeval;
typedef int t_bool;


typedef enum activity {
    EAT,
    SLEEP,
    THINK

} t_activity;

typedef struct s_philo_data {
    int         	num;
	pthread_t		philo;
    long long   	thread_start;
    long long   	last_eaten;
	struct s_data	*data;
}   t_philo_data;

typedef struct s_data {
    int         	total_num_philos;
    int         	min_rounds;
    int         	*rounds;
	pthread_mutex_t *forks;
    pthread_mutex_t mutex;
	pthread_mutex_t mutex_write;
    int         	time_to_sleep;
    int         	time_to_die;
    int         	time_to_eat;
	t_philo_data	*philos;
}   t_data;

//utils
t_bool  	is_dead(t_philo_data *philo_data, int num);
void    	unlock(t_bool *mutex);
void    	lock(t_bool *mutex, t_philo_data *philo_data, int num);
void    	do_activity(t_philo_data *philo_data, t_activity activity, char *activity_str);
double		get_s(t_timeval time);
void  	  	my_usleep(double wait_usec);
void	output(t_philo_data *philo, char *activity_str);
void	wait_for_death(t_data *data);
long long	get_current_millis();
int			get_mils_start(long long current, long long start);
void		lock_right_fork(t_philo_data *philo_data);
// void		take_fork_print(t_philo_data *philo_data);
void		set_var(t_philo_data *philo_data, int *dest, int source);
void	unlock_right_fork(t_philo_data *philo_data);
int	ft_max(int num1, int num2);
int	ft_min(int num1, int num2);

//init
void	init_data(t_data *data, char **argv, char argc);
long long   *create_time_arr(int num);
pthread_t   *init_philos(int num);


void    putstr_arg(char *str, long long arg, char c);

#endif