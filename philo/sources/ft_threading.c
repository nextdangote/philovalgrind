#include "../include/philosophers.h"

void    *ft_philo_life_routine(void *param)
{
    t_philo *philo;

    philo = (t_philo*)param;
    printf("philo id is %d\n", philo->index);
    if(philo->index % 2 == 0)
        ft_usleep(1);
    while(1)//dead_or_alive(philo))
    {
        ft_eat(philo);
        ft_sleep(philo);
        ft_think(philo);
    }
    return (philo);
}

void    ft_threading(t_philo *philo)
{
    int	i;
	int amount_of_threads;
    pthread_t   checker = 0;

	i = 0;
	amount_of_threads = philo[i].amount;
    printf("%d\n", amount_of_threads);
    pthread_create(&checker, NULL, ft_checker, &philo);
	while(i < amount_of_threads)
	{
		pthread_create(&philo[i].thread_phil, NULL, ft_philo_life_routine, &philo[i]);
        i++;
	}

    i = 0;
    pthread_join(checker, NULL);
    // while(i < amount_of_threads)
	// {
	// 	pthread_join(philo[i].thread_phil, NULL);
    //     i++;
    // }
    ft_pjoin(philo);
}

pthread_t  *ft_create_threads(int amount)
{
    pthread_t  *threads;

    threads = (pthread_t *) malloc (sizeof(pthread_t) * amount);
    return(threads);
}