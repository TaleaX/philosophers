#include "../inc/philo.h"

t_timeval   *create_time_arr(int num)
{
    t_timeval   *times;
    int         i;

    times = malloc(sizeof(t_timeval) * (num));
    if (!times)
        return (NULL);
    i = 0;
    while (i < num)
    {
        gettimeofday(times + i, NULL);
        i++;
    }
    return (times);
}

t_timeval   *create_time_start_arr(int num)
{
    long long   *times;

    times = malloc(sizeof(long long) * (num));
    if (!times)
        return (NULL);
    return (times);
}

static pthread_mutex_t *create_forks(int num)
{
    pthread_mutex_t *forks;
    int i;

    forks = malloc(sizeof(pthread_mutex_t) * (num));
    if (!forks)
        return (NULL);
    i = 0;
    while (i < num)
    {
        pthread_mutex_init(&forks[i], NULL);
        i++;
    }
    return (forks);
}

// static t_bool *create_forks_b(int num)
// {
//     t_bool *forks;
//     int i;

//     forks = malloc(sizeof(t_bool) * (num));
//     if (!forks)
//         return (NULL);
//     i = 0;
//     while (i < num)
//     {
//         forks[i] = FALSE;
//         i++;
//     }
//     return (forks);
// }

pthread_t   *init_philos(int num)
{
    pthread_t   *philos;

    philos = malloc(sizeof(pthread_t) * num);
    return (philos);

}

void    init_philo_data(t_philo_data *philo_data, char **argv, char argc)
{
    philo_data->num_forks = atoi(argv[1]);
    philo_data->total_num_philos = atoi(argv[1]);
    philo_data->forks = create_forks(atoi(argv[1]));
    //philo_data->forks_b = create_forks_b(atoi(argv[1]));
    philo_data->time_to_die = atoi(argv[2]);
    philo_data->time_to_eat = atoi(argv[3]);
    philo_data->time_to_sleep = atoi(argv[4]);
	philo_data->time_arr = create_time_arr(philo_data->total_num_philos);
    philo_data->time_thread_start = create_time_start_arr(philo_data->total_num_philos);
	philo_data->mutex = malloc(sizeof(pthread_mutex_t));
    philo_data->mutex_write = malloc(sizeof(pthread_mutex_t));
    pthread_mutex_init(philo_data->mutex, NULL);
    pthread_mutex_init(philo_data->mutex_write, NULL);
	philo_data->min_rounds = -1;
    philo_data->rounds = malloc(sizeof(int));
    *philo_data->rounds = 0;
	if (argc > 5)
		philo_data->min_rounds = atoi(argv[5]) * philo_data->total_num_philos;
}
