/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_action.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguede <aguede@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 16:58:52 by aguede            #+#    #+#             */
/*   Updated: 2023/10/25 16:58:53 by aguede           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	ft_die(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	*(philo->dead) = 1;
	pthread_mutex_unlock(philo->dead_lock);
	ft_print_action("died\n", philo);
}

void	ft_eat(t_philo *philo)
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
	pthread_mutex_unlock(philo->food_lock);
	ft_usleep(philo->time_to_eat);
	philo->in_degustation = 0;
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return ;
}

void	ft_sleep(t_philo *philo)
{
	ft_print_action("is sleeping\n", philo);
	ft_usleep(philo->time_to_sleep);
	return ;
}

void	ft_think(t_philo *philo)
{
	ft_print_action("is thinking\n", philo);
	return ;
}
