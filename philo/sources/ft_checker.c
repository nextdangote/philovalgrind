/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checker.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguede <aguede@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 17:50:41 by aguede            #+#    #+#             */
/*   Updated: 2023/10/25 17:53:24 by aguede           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	ft_check_all_eat(t_philo *philos)
{
	int	i;
	int	finished_eating;

	i = 0;
	finished_eating = 0;
	if (philos[0].total_eating_round == 0)
		return (0);
	while (i < philos[0].amount)
	{
		pthread_mutex_lock(philos->food_lock);
		if (philos[i].eating_round >= (philos->total_eating_round))
		{
			finished_eating++;
		}
		pthread_mutex_unlock(philos->food_lock);
		i++;
	}
	if (finished_eating == philos[0].amount)
	{
		pthread_mutex_lock(philos->dead_lock);
		*philos->dead = 1;
		pthread_mutex_unlock(philos->dead_lock);
		return (1);
	}
	return (0);
}

int	ft_check_death(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo[0].amount)
	{
		pthread_mutex_lock(philo[0].dead_lock);
		pthread_mutex_lock(philo[i].food_lock);
		if (get_proper_time() - philo->last_meal_time >= philo[0].time_to_die)
		{
			printf("%lu %d %s", get_proper_time() - philo->start_time,
				philo->index, "died\n");
			*philo->dead = 1;
			pthread_mutex_unlock(philo[i].food_lock);
			pthread_mutex_unlock(philo[0].dead_lock);
			return (1);
		}
		pthread_mutex_unlock(philo[i].food_lock);
		pthread_mutex_unlock(philo[0].dead_lock);
		i++;
	}
	return (0);
}

void	*ft_checker(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	usleep(philo->time_to_die * (1000 - 1));
	while (1)
	{
		if (ft_check_all_eat(philo) == 1 || ft_check_death(philo) == 1)
		{
			break ;
		}
	}
	return (philo);
}
