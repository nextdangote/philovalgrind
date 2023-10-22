#include "../include/philosophers.h"

void    ft_error_message(char *str)
{
    printf("%s\n", str);
    exit(1);
}

void    ft_print_action(char *str, t_philo *philo)
{
    pthread_mutex_lock(philo->print_lock);
    if(dead_or_alive(philo))
        printf("%lu %d %s", get_proper_time() - philo->start_time,  philo->index, str);
    pthread_mutex_unlock(philo->print_lock);
}

void    ft_destroy(t_philo *philo)
{
    int i;

    i = 0;
    pthread_mutex_destroy(philo->dead_lock);
    //pthread_mutex_destroy(philo->sleep_lock);
    pthread_mutex_destroy(philo->food_lock);
    pthread_mutex_destroy(philo->print_lock);
    while (i < philo->amount)
    {
        pthread_mutex_destroy(philo[i].left_fork);
        i++;
    }
}

void ft_pjoin(t_philo *philo)
{
    int i;
    int amount;

    i = 0;
    amount = philo[0].amount;
    while (i < amount)
    {
        if(pthread_join(philo[i].thread_phil, NULL) != 0)
        {
            ft_destroy(philo);
            break;
        }
        printf("join thread phil %d\n", i);
        i++;
    }
}

int get_proper_time()
{
    struct timeval time_struct;
    int time;

    gettimeofday(&time_struct, NULL);
    time = (time_struct.tv_sec * 1000) + (time_struct.tv_usec / 1000);
    return(time);
}

void ft_usleep(size_t msec)
{
    size_t beginning;

    beginning = get_proper_time();
    while((get_proper_time() - beginning) < msec)
    {
        usleep(500);// why 500 and not something else ?
    }
}