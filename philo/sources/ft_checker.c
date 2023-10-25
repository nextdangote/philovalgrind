#include "../include/philosophers.h"
// void    ft_destroy_threads(t_philo  *philo)
// {
//     int i;

//     i = 0;
//     pthread_mutex_destroy(philo->dead_lock);
//     pthread_mutex_destroy(philo->sleep_lock);
//     pthread_mutex_destroy(philo->food_lock);
//     pthread_mutex_destroy(philo->print_lock);
//     while (i < philo.amount)
//     {
//         pthread_mutex_destroy(&philo[i].left_fork);
//         pthread_mutex_destroy(&philo[i].right_fork);
//         i++;
//     }
// }

// void    ft_mfucker_died(t_philo *philo)
// {

// }

// int    ft_check_all_eat(t_philo *philo)
// {
//     int end;
//     int value;
//     static int i = 0;
//     end = (philo->total_eating_round * (philo[0].amount - 1)) + 1;
//     // if (i == 0)
//     // {
//     //     printf("end = %d\n", end);
//     //     i++;
//     // }
//     pthread_mutex_lock(philo->food_lock);
//     value = *(philo->meals_total);
//     printf("value is %d\n", value);
//     //pthread_mutex_lock(philo->meals_count_lock);
//     if (value <= end)
//     {
//         *philo->dead = 1;
//         pthread_mutex_unlock(philo->food_lock);
//         //pthread_mutex_unlock(philo->meals_count_lock);
//         return(1);
//     }
//     //pthread_mutex_unlock(philo->meals_count_lock);
//     pthread_mutex_unlock(philo->food_lock);
//     return(0);
// }


int	ft_check_all_eat(t_philo *philos)
{
	int	i;
	int	finished_eating;
    int nbr_philo = philos[0].amount;

	i = 0;
	finished_eating = 0;
	if (philos[0].total_eating_round == 0)
		return (0);
	while (i < nbr_philo)
	{
		pthread_mutex_lock(philos->food_lock);
		if (philos[i].eating_round >= (philos->total_eating_round))
        {
			finished_eating++;
            //printf("%d philo finished eating\n", finished_eating);
            //pthread_mutex_unlock(philos[i].food_lock);
        }
		pthread_mutex_unlock(philos->food_lock);
		i++;
	}
	if (finished_eating == nbr_philo)
	{
		pthread_mutex_lock(philos->dead_lock);
		*philos->dead = 1;
		pthread_mutex_unlock(philos->dead_lock);
		return (1);
	}
	return (0);
}

int   ft_check_death(t_philo *philo)
{
    int i;

    i = 0;
    while(i < philo[0].amount)
    {
        pthread_mutex_lock(philo[0].dead_lock);
        pthread_mutex_lock(philo[i].food_lock);
		//printf("checking if dead %d\n", i);
        if(get_proper_time() - philo->last_meal_time >= philo[0].time_to_die)
        {
			// printf("is dead %d\n", i);
			// ft_print_action("died", philo);
			//pthread_mutex_lock(philo->print_lock);
        	printf("%lu %d %s", get_proper_time() - philo->start_time,  philo->index, "died\n");
			*philo->dead = 1;
    		//pthread_mutex_unlock(philo->print_lock);
            pthread_mutex_unlock(philo[i].food_lock);
            pthread_mutex_unlock(philo[0].dead_lock);
            return(1);
        }
		pthread_mutex_unlock(philo[i].food_lock);
        pthread_mutex_unlock(philo[0].dead_lock);
        i++;
    }
    return(0);
}

void    *ft_checker(void *param)
{
    t_philo *philo;
    philo = (t_philo*)param;
	usleep(philo->time_to_die * (1000 - 1));
    while(1)
    {
        if(ft_check_all_eat(philo) == 1 || ft_check_death(philo) == 1)
        {
            break;
        }
    }
    return(philo);
}