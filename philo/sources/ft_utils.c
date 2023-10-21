#include "../include/philosophers.h"

void    ft_error_message(char *str)
{
    printf("%s\n", str);
    exit(1);
}

void    ft_print_action(char *str, t_philo *philo)
{
    pthread_mutex_lock(philo->print_lock);
    printf("%lu ", get_proper_time() - philo->start_time);
    printf("%d ", philo->index);
    printf("%s", str);
    pthread_mutex_unlock(philo->print_lock);
}

void    ft_destroy(pthread_mutex_t *forks, int amount, t_philo *philo)
{
    int i;

    i = 0;
    pthread_mutex_destroy(philo->dead_lock);
    pthread_mutex_destroy(philo->sleep_lock);
    pthread_mutex_destroy(philo->food_lock);
    pthread_mutex_destroy(philo->print_lock);
    while (i < amount)
    {
        pthread_mutex_destroy(&forks[i]);
        pthread_mutex_destroy(&philo[i].left_fork);
        pthread_mutex_destroy(&philo[i].right_fork);
        i++;
    }
}

void ft_pjoin(t_philo *philo)
{
    int i;
    int amount;

    i = 0;
    amount = philo[i].amount;
    while (i < amount)
    {
        pthread_join(philo[i].thread_phil, NULL);
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