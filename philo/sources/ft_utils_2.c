#include "../include/philosophers.h"

int dead_or_alive(t_philo *philo)
{
    pthread_mutex_lock(philo->dead_lock);
    if (*philo->dead == 1)
    {
        pthread_mutex_unlock(philo->dead_lock);
        return(0);
    }
    pthread_mutex_unlock(philo->dead_lock);
    return(1);
}
