#include "../inc/philo.h"

void    *rountine(void *content)
{
    t_philo_data *philo_data = content;


    printf("test begin philo num %d\n", philo_data.num);
    usleep(300000);
    printf("end \n");
    return NULL;
}

pthread_t   *init_philos(int num)
{
    pthread_t   *philos;

    philos = malloc(sizeof(pthread_t) * num);
    return (philos);

}

t_bool *create_forks(int num)
{
    t_bool *forks;
    int i;

    forks = malloc(sizeof(t_bool) * (num));
    if (!forks)
        return (NULL);
    i = 0;
    while (i < num)
    {
        forks[i] = 0;
        i++;
    }
    return (forks);
}

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

void    init_philo_data(t_philo_data *philo_data, char **argv)
{
    philo_data->num_forks = atoi(argv[1]);
    philo_data->forks = create_forks(atoi(argv[1]));
    philo_data->time_to_die = atoi(argv[2]);
    philo_data->time_to_eat = atoi(argv[3]);
    philo_data->time_to_sleep = atoi(argv[4]);
    philo_data->time_arr = create_time_arr(atoi(argv[1]));
}


int main(int argc, char **argv)
{
    int num_philos = atoi(argv[1]);
    t_philo_data    philo_data;
    pthread_t       *philos;
    int             i;

    philos = init_philos(num_philos);
    init_philo_data(&philo_data, argv);
    (void)argc;
    i = 0;
    while (i < atoi(argv[1]))
    {
        //gettimeofday(&time, NULL);
        printf("current time %d = %ld\n", i, philo_data.time_arr[i].tv_usec);
        i++;
    }
    i = 0;
    while (i < num_philos)
    {
        philo_data.num = i;
        pthread_create(&philos[i], NULL, &rountine, &philo_data);
        i++;

    }
    i = 0;
    while (i < num_philos)
    {
        pthread_join(philos[i], NULL);
        i++;
    }
    printf("well\n");
    return 0;
}