/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguede <aguede@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 18:07:05 by aguede            #+#    #+#             */
/*   Updated: 2023/10/25 18:07:54 by aguede           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

t_philo	*ft_init_philo_part2(t_philo *philo, int argc, char **argv)
{
	int		i;
	int		j;
	size_t	time;

	time = get_proper_time();
	i = 0;
	j = 0;
	while (i < ft_atoi(argv[1]))
	{
		philo[i].full = FALSE;
		philo[i].dead = &j;
		philo[i].amount = ft_atoi(argv[1]);
		philo[i].start_time = time;
		philo[i].last_meal_time = time;
		philo[i].time_to_die = (size_t)ft_atoi(argv[2]);
		philo[i].time_to_eat = (size_t)ft_atoi(argv[3]);
		philo[i].time_to_sleep = (size_t)ft_atoi(argv[4]);
		philo[i].eating_round = 0;
		if (argc == 6)
			philo[i].total_eating_round = ft_atoi(argv[5]);
		else
			philo[i].total_eating_round = 0;
		i++;
	}
	return (philo);
}

t_philo	*ft_init_philos(pthread_mutex_t *forks, t_philo *philo, int argc,
		char **argv)
{
	philo = (t_philo *)malloc(sizeof(t_philo) * ft_atoi(argv[1]));
	if (!philo)
		return (NULL);
	philo = ft_init_philo_part2(philo, argc, argv);
	ft_init_forks(forks, ft_atoi(argv[1]), philo);
	return (philo);
}

t_philo	*ft_init_philo_threads(t_philo *philo, pthread_t *thread,
		int amount_of_philos, t_my_locks *my_locks)
{
	int	i;

	i = 0;
	while (i < amount_of_philos)
	{
		philo[i].thread_phil = thread[i];
		philo[i].index = i + 1;
		philo[i].food_lock = my_locks->food_lock;
		philo[i].print_lock = my_locks->print_lock;
		philo[i].dead_lock = my_locks->dead_lock;
		philo[i].meals_count_lock = my_locks->meals_count_lock;
		philo[i].eating_round = 0;
		philo[i].in_degustation = 0;
		i++;
	}
	return (philo);
}
