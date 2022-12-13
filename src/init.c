#include "../inc/philo.h"

// t_timeval   *create_time_arr(int num)
// {
//     t_timeval   *times;
//     int         i;

//     times = malloc(sizeof(t_timeval) * (num));
//     if (!times)
//         return (NULL);
//     i = 0;
//     while (i < num)
//     {
//         gettimeofday(times + i, NULL);
//         i++;
//     }
//     return (times);
// }

// long long   *create_time_arr(int num)
// {
//     long long   *times;
//     int         i;

//     times = malloc(sizeof(long long) * (num));
//     if (!times)
//         return (NULL);
//     i = 0;
//     while (i < num)
//     {
//         times[i++] = 0;
//     }
//     return (times);
// }

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
//         forks[i] = TRUE;
//         i++;
//     }
//     return (forks);
// }

// pthread_t   *init_philos(int num)
// {
//     pthread_t   *philos;

//     philos = malloc(sizeof(pthread_t) * num);
//     return (philos);

// }

static t_philo_data	*init_philo_data(int len, t_data *data)
{
	t_philo_data	*philo_data;
	int		i;

	philo_data = malloc(sizeof(philo_data) * len);
	if (!philo_data)
		return (NULL);
	i = 0;
	while (i < len)
	{
		philo_data[i].last_eaten = 0;
		philo_data[i].thread_start = 0;
		philo_data[i].data = data;
		philo_data[i].num = i;
		philo_data[i].first_fork = ft_min(i, (i + 1) % len);
		philo_data[i].sec_fork = ft_max(i, (i + 1) % len);
		// pthread_mutex_init(&philo_data[i].fork_left, NULL);
		i++;
	}
	return (philo_data);
}

void	init_data(t_data *data, char **argv, char argc)
{
    data->total_num_philos = atoi(argv[1]);
    data->time_to_die = atoi(argv[2]);
    data->time_to_eat = atoi(argv[3]);
    data->time_to_sleep = atoi(argv[4]);
	data->alive = TRUE;
	data->forks = create_forks(atoi(argv[1]));
	pthread_mutex_init(&data->mutex, NULL);
    pthread_mutex_init(&data->mutex_write, NULL);
	data->min_rounds = -1;
    data->rounds = malloc(sizeof(int));
    *data->rounds = 0;
	if (argc > 5)
		data->min_rounds = atoi(argv[5]) * data->total_num_philos;
	data->philos = init_philo_data(data->total_num_philos, data);
}