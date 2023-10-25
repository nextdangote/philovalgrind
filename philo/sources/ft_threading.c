#include "../include/philosophers.h"

void    *ft_philo_life_routine(void *param)
{
    t_philo *philo;

    philo = (t_philo*)param;
    if(philo->index % 2 == 0)
         ft_usleep(1);
    while(dead_or_alive(philo))
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
    if (pthread_create(&checker, NULL, ft_checker, philo) != 0)
    {
        printf("error creating thread philo");
        ft_destroy(philo);
    }
	while(i < amount_of_threads)
	{
		if (pthread_create(&philo[i].thread_phil, NULL, ft_philo_life_routine, &philo[i]) != 0)
        {
            printf("error creating thread checker\n");
            ft_destroy(philo);
        }
        i++;
	}

    i = 0;
    if (pthread_join(checker, NULL) != 0)
    {
        printf("error joining thread checker");
        ft_destroy(philo);
    }
    while(i < amount_of_threads)
	{
		if(pthread_join(philo[i].thread_phil, NULL) != 0)
        {
            printf("error creating thread philo");
            ft_destroy(philo);
        }
        i++;
    }
    //ft_pjoin(philo);
}

pthread_t  *ft_create_threads(int amount)
{
    pthread_t  *threads;

    threads = (pthread_t *) malloc (sizeof(pthread_t) * amount);
    return(threads);
}