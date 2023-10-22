#include "../include/philosophers.h"

void ft_die(t_philo *philo)
{
    pthread_mutex_lock(philo->dead_lock);
    *(philo->dead) = 1;
    pthread_mutex_unlock(philo->dead_lock);
    //ft_print_action("died\n", philo, i);
}

void ft_eat(t_philo *philo)
{
    pthread_mutex_lock(philo->right_fork);
    ft_print_action("has taken a fork\n", philo);
    pthread_mutex_lock(philo->left_fork);
    ft_print_action("has taken a fork\n", philo);
    philo->in_degustation = 1;
    ft_print_action("is eating\n", philo);
    pthread_mutex_lock(philo->food_lock);
    philo->last_meal_time = get_proper_time();
    philo->eating_round++;
    //printf("meals eaten for philo %d is %d\n", philo->index, philo->eating_round);
    pthread_mutex_unlock(philo->food_lock);
    //on incremente le nombre de repas mange
    ft_usleep(philo->time_to_eat);
    philo->in_degustation = 0;
    //usleep(10000);
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);
    return;
}

// void	eat(t_philo *philo)
// {
// 	pthread_mutex_lock(philo->r_fork);
// 	print_message("has taken a fork", philo, philo->id);
// 	if (philo->num_of_philos == 1)
// 	{
// 		ft_usleep(philo->time_to_die);
// 		pthread_mutex_unlock(philo->r_fork);
// 		return ;
// 	}
// 	pthread_mutex_lock(philo->l_fork);
// 	print_message("has taken a fork", philo, philo->id);
// 	philo->eating = 1;
// 	print_message("is eating", philo, philo->id);
// 	pthread_mutex_lock(philo->meal_lock);
// 	philo->last_meal = get_current_time();
// 	philo->meals_eaten++;
// 	//printf("meals eaten for philo %d is %d\n", philo->id, philo->meals_eaten);
// 	pthread_mutex_unlock(philo->meal_lock);
// 	ft_usleep(philo->time_to_eat);
// 	philo->eating = 0;
// 	pthread_mutex_unlock(philo->l_fork);
// 	pthread_mutex_unlock(philo->r_fork);
// }

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
    ft_print_action("is thinking\n", philo);   
    return;
}
