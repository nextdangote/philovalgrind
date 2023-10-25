/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguede <aguede@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 17:54:24 by aguede            #+#    #+#             */
/*   Updated: 2023/10/25 18:07:45 by aguede           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

pthread_mutex_t	*ft_forks_creation(int i)
{
	int				j;
	pthread_mutex_t	*fork;

	j = 0;
	fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * i);
	if (!fork)
		return (NULL);
	while (j < i)
	{
		pthread_mutex_init(&fork[j], NULL);
		j++;
	}
	return (fork);
}

void	ft_init_forks(pthread_mutex_t *fork, int amount, t_philo *philo)
{
	int	i;

	i = 0;
	if (!fork)
		return ;
	while (i < amount)
	{
		philo[i].left_fork = &fork[i];
		if (i == 0)
			philo[i].right_fork = &fork[amount - 1];
		else
			philo[i].right_fork = &fork[i - 1];
		i++;
	}
}

t_my_locks	*ft_create_my_locks(void)
{
	t_my_locks		*my_locks;
	pthread_mutex_t	*food_lock;
	pthread_mutex_t	*print_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meals_count_lock;

	my_locks = (t_my_locks *)malloc(sizeof(t_my_locks));
	if (!my_locks)
		exit(1);
	food_lock = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	print_lock = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	dead_lock = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	meals_count_lock = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!food_lock || !print_lock || !dead_lock || !meals_count_lock)
		exit(1);
	pthread_mutex_init(food_lock, NULL);
	pthread_mutex_init(print_lock, NULL);
	pthread_mutex_init(dead_lock, NULL);
	pthread_mutex_init(meals_count_lock, NULL);
	my_locks->dead_lock = dead_lock;
	my_locks->food_lock = food_lock;
	my_locks->print_lock = print_lock;
	my_locks->meals_count_lock = meals_count_lock;
	return (my_locks);
}
