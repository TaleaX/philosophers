#include "../inc/philo.h"

t_bool  mutex_for_lock = FALSE;
t_bool forks_b[2] = {FALSE, FALSE};

void    *routine(void *content)
{

    t_philo_data philo_data = *(t_philo_data *)content;
    t_timeval   time_death;
    int eat;
    int i = 0;
    while (1)
    {
        if (is_dead(&philo_data))
        {
            printf("Philo %d died: Timestap m %d\n", philo_data.num, philo_data.time_death.tv_usec);
            pthread_exit(NULL);
        }
        printf("philo num %d is thinking\n", philo_data.num);
        lock(&philo_data.forks_b[philo_data.num], philo_data);
        lock(&philo_data.forks_b[(philo_data.num + 1) % philo_data.total_num_philos], philo_data);
        printf("philo num %d finished thinking\n", philo_data.num);
        do_activity(philo_data, EAT, EAT_STR);
        gettimeofday(philo_data.time_arr + philo_data.num, NULL);
        unlock(&philo_data.forks_b[philo_data.num]);
        unlock(&philo_data.forks_b[(philo_data.num + 1) % philo_data.total_num_philos]);
        do_activity(philo_data, SLEEP, SLEEP_STR);
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
