#include "../inc/philo.h"

int num = 0;

t_bool  mutex_for_lock = FALSE;
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

void    lock(t_bool *mutex, t_philo_data philo_data)
{
    while (*mutex)
    {
        if (is_dead(philo_data))
            pthread_exit(NULL);
    }
    *mutex = TRUE;
}

void    unlock(t_bool *mutex)
{
    *mutex = FALSE;
}

t_bool  is_dead(t_philo_data philo_data)
{
    t_timeval   current_time;
    t_timeval   time_last_meal;

    lock(&mutex_for_lock, philo_data);
    time_last_meal = philo_data.time_arr[philo_data.num];
    gettimeofday(&current_time, NULL);
    unlock(&mutex_for_lock);
    printf("current %d last meal %d diff %d\n", current_time.tv_usec, time_last_meal.tv_usec, current_time.tv_usec - time_last_meal.tv_usec);
    if (current_time.tv_usec - time_last_meal.tv_usec > philo_data.time_to_die)
    {
        lock(&mutex_for_lock, philo_data);
        philo_data.time_death = current_time;
        unlock(&mutex_for_lock);
        return (TRUE);
    }
    return (FALSE);
}

void    *routine(void *content)
{

    t_philo_data *philo_data = (t_philo_data *)content;
    t_timeval   time_death;
    int eat;
    int i = 0;
    philo_data->time_arr = create_time_arr(philo_data->total_num_philos);
    while (1)
    {
        if (is_dead(*philo_data))
        {
            lock(&mutex_for_lock, *philo_data);
            gettimeofday(&time_death, NULL);
            unlock(&mutex_for_lock);
            printf("Philo %d died: Timestap m %d\n", philo_data->num, philo_data->time_death.tv_usec);
            pthread_exit(NULL);
        }
        printf("philo num %d is thinking\n", philo_data->num);
        lock(&philo_data->forks_b[philo_data->num], *philo_data);
        lock(&philo_data->forks_b[(philo_data->num + 1) % philo_data->total_num_philos], *philo_data);
        printf("philo num %d starts eating\n", philo_data->num);
        usleep(philo_data->time_to_eat * 1000);
        gettimeofday(philo_data->time_arr + philo_data->num, NULL);
        i++;
        printf("philo num %d finished eating\n", philo_data->num);
        unlock(&philo_data->forks_b[philo_data->num]);
        unlock(&philo_data->forks_b[(philo_data->num + 1) % philo_data->total_num_philos]);
        printf("philo num %d starts sleeping\n", philo_data->num);
        usleep(philo_data->time_to_sleep * 1000);
        printf("philo num %d finished sleeping\n", philo_data->num);
    }
    printf("test begin philo num %d\n", philo_data->num);
    usleep(300000);
    printf("end %d\n", philo_data->num);
    return NULL;
}

pthread_t   *init_philos(int num)
{
    pthread_t   *philos;

    philos = malloc(sizeof(pthread_t) * num);
    return (philos);

}

pthread_mutex_t *create_forks(int num)
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

t_bool *create_forks_b(int num)
{
    t_bool *forks;
    int i;

    forks = malloc(sizeof(t_bool) * (num));
    if (!forks)
        return (NULL);
    i = 0;
    while (i < num)
    {
        forks[i] = TRUE;
        i++;
    }
    return (forks);
}


void    init_philo_data(t_philo_data *philo_data, char **argv)
{
    philo_data->num_forks = atoi(argv[1]);
    philo_data->total_num_philos = atoi(argv[1]);
    philo_data->forks = create_forks(atoi(argv[1]));
    philo_data->forks_b = create_forks_b(atoi(argv[1]));
    philo_data->time_to_die = atoi(argv[2]);
    philo_data->time_to_eat = atoi(argv[3]);
    philo_data->time_to_sleep = atoi(argv[4]);
}



int main(int argc, char **argv)
{
    int num_philos = atoi(argv[1]);
    t_philo_data    philo_data;
    pthread_t       *philos;
    int             i;

    if (argc >= 5)
    {
        philos = init_philos(num_philos);
        init_philo_data(&philo_data, argv);
        
        i = 0;
        // while (i < atoi(argv[1]))
        // {
        //     //gettimeofday(&time, NULL);
        //     printf("current time %d = %ld\n", i, philo_data.time_arr[i].tv_usec);
        //     i++;
        // }
        i = 0;
        while (i < num_philos)
        {
            //philo_data.num = malloc(sizeof(int));
            philo_data.num = i;
            pthread_create(&philos[i], NULL, &routine, (void *)&philo_data);
            usleep(100);
            i++;

        }
        i = 0;
        while (i < num_philos)
        {
            pthread_join(philos[i], NULL);
            i++;
        }
        printf("well %d\n", philo_data.num_forks);
        //pthread_mutex_destroy(&mutex);
    }
    printf("num = %d\n", num);
    return 0;
}