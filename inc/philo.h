#ifndef PHILO_H
# define PHILO_H

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>

#define TRUE 1
#define FALSE 0
#define EAT_STR "eating"
#define SLEEP_STR "sleeping"
#define THINK_STR "thinking"

typedef struct timeval t_timeval;
typedef int t_bool;


typedef enum activity {
    EAT,
    SLEEP,
    THINK

} t_activity;

typedef struct s_philo_data {
    int         num;
    int         total_num_philos;
    int         min_rounds;
    int         *rounds;
    int         num_forks;
    pthread_mutex_t *mutex;
    pthread_mutex_t *mutex_activity;
    pthread_mutex_t *forks;
    t_bool          *forks_b;
    int         time_to_sleep;
    int         time_to_die;
    int         time_to_eat;
    //t_timeval   *time_arr;
    long long   *time_thread_start;
    long long   *time_current;
    long long   *time_last_eaten;
    t_timeval  time_death;
}   t_philo_data;

//utils
t_bool  is_dead(t_philo_data *philo_data, int num);
void    unlock(t_bool *mutex);
void    lock(t_bool *mutex, t_philo_data *philo_data, int num);
void    do_activity(t_philo_data *philo_data, t_activity activity, char *activity_str);
double	get_s(t_timeval time);
void    my_usleep(double wait_usec);
void	output(t_philo_data *philo_data, char *activity_str);
void	wait_for_death(t_philo_data philo_data);
long long	get_current_millis();
int	get_mils_start(long long current, long long start);

//init
void    init_philo_data(t_philo_data *philo_data, char **argv, char argc);
long long   *create_time_arr(int num);
pthread_t   *init_philos(int num);


void    putstr_arg(char *str, long long arg, char c);

#endif