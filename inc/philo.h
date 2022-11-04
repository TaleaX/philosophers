#ifndef PHILO_H
# define PHILO_H

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>

#define TRUE 1
#define FALSE 0

typedef struct timeval t_timeval;
typedef int t_bool;

typedef struct s_philo_data {
    int         num;
    int         num_forks;
    t_bool      *forks;
    int         time_to_sleep;
    int         time_to_die;
    int         time_to_eat;
    t_timeval  *time_arr;
}   t_philo_data;

#endif