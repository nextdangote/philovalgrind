/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_threading.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguede <aguede@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 18:11:53 by aguede            #+#    #+#             */
/*   Updated: 2023/10/25 18:56:31 by aguede           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	*ft_philo_life_routine(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	if (philo->index % 2 == 0)
		ft_usleep(1);
	while (dead_or_alive(philo))
	{
		ft_eat(philo);
		ft_sleep(philo);
		ft_think(philo);
	}
	return (philo);
}

void	ft_threading(t_philo *philo, pthread_mutex_t *forks,
		t_my_locks *my_locks, pthread_t *threads)
{
	int			i;
	int			amount_of_threads;
	pthread_t	checker;

	checker = 0;
	i = 0;
	amount_of_threads = philo[i].amount;
	if (pthread_create(&checker, NULL, ft_checker, philo) != 0)
		ft_destroy(philo, forks, my_locks, threads);
	while (i < amount_of_threads)
	{
		if (pthread_create(&philo[i].thread_phil, NULL, ft_philo_life_routine,
				&philo[i]) != 0)
			ft_destroy(philo, forks, my_locks, threads);
		i++;
	}
	i = 0;
	if (pthread_join(checker, NULL) != 0)
		ft_destroy(philo, forks, my_locks, threads);
	while (i < amount_of_threads)
	{
		if (pthread_join(philo[i].thread_phil, NULL) != 0)
			ft_destroy(philo, forks, my_locks, threads);
		i++;
	}
}

pthread_t	*ft_create_threads(int amount)
{
	pthread_t	*threads;

	threads = (pthread_t *)malloc(sizeof(pthread_t) * amount);
	return (threads);
}
