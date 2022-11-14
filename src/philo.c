#include "../inc/philo.h"

t_bool  mutex_for_lock = FALSE;
t_bool forks_b[2] = {FALSE, FALSE};

void    *routine(void *content)
{

    t_philo_data *philo_data = (t_philo_data *)content;
    t_timeval   time_death;
    static int  num = -1;

    pthread_mutex_lock(&philo_data->mutex_for_lock);
    num++;
    gettimeofday(philo_data->time_arr + num, NULL);
    pthread_mutex_unlock(&philo_data->mutex_for_lock);
    while (1)
    {
        if (is_dead(philo_data, num))
        {
            printf("Philo %d died: Timestap m %d\n", num, philo_data->time_death.tv_usec);
            pthread_exit(NULL);
        }
        printf("philo num %d is thinking\n", num);
        lock(&philo_data->forks_b[num], philo_data, num);
        lock(&philo_data->forks_b[(num + 1) % philo_data->total_num_philos], philo_data, num);
        printf("philo num %d finished thinking\n", num);
        do_activity(*philo_data, EAT, EAT_STR, num);
        gettimeofday(philo_data->time_arr + num, NULL);
        unlock(&philo_data->forks_b[num]);
        unlock(&philo_data->forks_b[(num + 1) % philo_data->total_num_philos]);
        do_activity(*philo_data, SLEEP, SLEEP_STR, num);
    }
    return NULL;
}

pthread_t   *init_philos(int num)
{
    pthread_t   *philos;

    philos = malloc(sizeof(pthread_t) * num);
    return (philos);

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
        philo_data.time_arr = create_time_arr(philo_data.total_num_philos);
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
        //pthread_mutex_destroy(&mutex);
    }
    return 0;
}