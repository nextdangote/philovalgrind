/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguede <aguede@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 18:16:46 by aguede            #+#    #+#             */
/*   Updated: 2023/10/25 18:19:09 by aguede           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	dead_or_alive(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead == 1)
	{
		pthread_mutex_unlock(philo->dead_lock);
		return (0);
	}
	pthread_mutex_unlock(philo->dead_lock);
	return (1);
}

void	ft_pjoin(t_philo *philo)
{
	int	i;
	int	amount;

	i = 0;
	amount = philo[0].amount;
	while (i < amount)
	{
		if (pthread_join(philo[i].thread_phil, NULL) != 0)
			break ;
		printf("join thread phil %d\n", i);
		i++;
	}
}
