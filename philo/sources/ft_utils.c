/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguede <aguede@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 18:18:41 by aguede            #+#    #+#             */
/*   Updated: 2023/10/25 19:03:11 by aguede           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	ft_error_message(char *str)
{
	printf("%s\n", str);
	exit(1);
}

void	ft_print_action(char *str, t_philo *philo)
{
	pthread_mutex_lock(philo->print_lock);
	if (dead_or_alive(philo))
		printf("%lu %d %s", get_proper_time() - philo->start_time, philo->index,
			str);
	pthread_mutex_unlock(philo->print_lock);
}

void	ft_destroy(t_philo *philo, pthread_mutex_t *forks, t_my_locks *my_locks, pthread_t *threads)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(my_locks->dead_lock);
	pthread_mutex_destroy(my_locks->meals_count_lock);
	pthread_mutex_destroy(my_locks->food_lock);
	pthread_mutex_destroy(my_locks->print_lock);
	while (i < philo->amount)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	i = 0;
	// free(threads);
	// free(philo);
	// free(forks);
	// free(my_locks);
}

int	get_proper_time(void)
{
	struct timeval	time_struct;
	int				time;

	gettimeofday(&time_struct, NULL);
	time = (time_struct.tv_sec * 1000) + (time_struct.tv_usec / 1000);
	return (time);
}

void	ft_usleep(size_t msec)
{
	size_t	beginning;

	beginning = get_proper_time();
	while ((get_proper_time() - beginning) < msec)
		usleep(500);
}
