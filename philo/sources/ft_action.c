#include "../include/philosophers.h"

void ft_die(t_philo *philo)
{
    pthread_mutex_lock(philo->dead_lock);
    *(philo->dead) = TRUE;
    pthread_mutex_unlock(philo->dead_lock);
    //ft_print_action("died\n", philo, i);
}

void ft_eat(t_philo *philo)
{
    // if ((get_proper_time() - philo[i].last_meal_time) >= philo->time_to_die)
    //     ft_die(philo, i);
    //if only one philo it must die directly
    pthread_mutex_lock(&philo->right_fork);
    ft_print_action("has taken the right fork\n", philo);
    pthread_mutex_lock(&philo->left_fork);
    ft_print_action("has taken the left fork\n", philo);
    philo->in_degustation = 1;
    pthread_mutex_lock(philo->food_lock);
    (*philo->meals_total)++;
    philo->last_meal_time = get_proper_time();
    pthread_mutex_unlock(philo->food_lock);
    //on incremente le nombre de repas mange
    ft_print_action("is eating\n", philo);
    ft_usleep(philo->time_to_sleep);
    philo->in_degustation = 0;
    //usleep(10000);
    pthread_mutex_unlock(&philo->right_fork);
    pthread_mutex_unlock(&philo->right_fork);
    return;
}

void ft_sleep(t_philo *philo)
{
    ft_print_action("is sleeping\n", philo);
    //pthread_mutex_lock(philo[i].sleep_lock);
    ft_usleep(philo->time_to_sleep);
    //pthread_mutex_unlock(philo[i].sleep_lock);
    return;
}

void ft_think(t_philo *philo)
{
    //pthread_mutex_lock(&philo[i].lock);
    ft_print_action("is thinking\n", philo);
    //pthread_mutex_unlock(&philo[i].lock);    
    return;
}
