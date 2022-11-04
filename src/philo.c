#include "../inc/philo.h"

// void    *routine(t_philo_data philo_data)
// {
//     while (1)
//     {
//         if (still_alive())
//         {

//         }
//         else
//         {
//             printf()
//         }
//     }
// }

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

int main(int argc, char *argv[])
{
    //pthread_t       philosopher[atoi(argv[0])];
    t_philo_data    philo_data;
    //t_timeval       time;
    int             i;

    if (argc){printf("bam");};
    init_philo_data(&philo_data, argv);
    //philo_data.time_arr = create_time_arr(atoi(argv[1]));
    i = 0;
    printf("atgv %s\n", argv[1]);
    while (i < atoi(argv[1]))
    {
        //gettimeofday(&time, NULL);
        printf("current time %d = %ld\n", i, philo_data.time_arr[i].tv_usec);
        i++;
    }
    // while (i < philo_data.num)
    // {
    //     philo_data.num = i;
    //     pthread_create(&philosopher[i], NULL, &routine, &philo_data);
    //     i++;
    // }
    // pthread_join(&philosopher, NULL);
    return (0);
}