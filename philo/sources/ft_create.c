#include "../include/philosophers.h"
pthread_mutex_t *ft_forks_creation(int i)
{
	int j;
	pthread_mutex_t	*fork;
	
	j = 0;
	fork = (pthread_mutex_t *) malloc (sizeof(pthread_mutex_t) * i);
	if (!fork)
		return NULL;
	while(j < i)
	{
		pthread_mutex_init(&fork[j], NULL);
		j++;
	}
	return(fork);
}

void    ft_init_forks(pthread_mutex_t *fork, int amount, t_philo *philo)
{
    int i;

    i = 0;
	if (!fork)
		return;
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

t_philo	*ft_init_philo_part2(t_philo *philo, int argc, char **argv)
{
	int i;
	int j;
	size_t	time;

	time = get_proper_time();
	i = 0;
	j = 0;
	while(i < ft_atoi(argv[1]))
	{
		philo[i].full = FALSE;
		philo[i].dead = &j;
		philo[i].amount = ft_atoi(argv[1]);
		philo[i].index = i + 1;
		philo[i].start_time = time; //get_proper_time();//current_time.tv_usec;
		philo[i].last_meal_time = time; //get_proper_time();//current_time.tv_usec;
		philo[i].time_to_die = (size_t)ft_atoi(argv[2]);
		philo[i].time_to_eat = (size_t)ft_atoi(argv[3]);
		philo[i].time_to_sleep = (size_t)ft_atoi(argv[4]);
		philo[i].eating_round = 0;
		if(argc == 6)
			philo[i].total_eating_round = ft_atoi(argv[5]);
		else
			philo[i].total_eating_round = 0;
		i++;
	}
	return (philo);
}

t_philo    *ft_init_philos(pthread_mutex_t *forks, t_philo *philo, int argc, char **argv)
{
    philo = (t_philo *)malloc(sizeof(t_philo) * ft_atoi(argv[1]));
	if (!philo)
		return(NULL);
	philo = ft_init_philo_part2(philo, argc, argv);
	ft_init_forks(forks, ft_atoi(argv[1]), philo);
	return(philo);
}

t_philo	*ft_init_philo_threads(t_philo *philo, pthread_t *thread, int amount_of_philos, t_my_locks *my_locks)
{
	int	i;
	// pthread_mutex_t *food_lock = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
    // pthread_mutex_t *print_lock = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
    // pthread_mutex_t *dead_lock = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	// pthread_mutex_t *meals_count_lock = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));

	// pthread_mutex_init(food_lock, NULL);
	// pthread_mutex_init(print_lock, NULL);
	// pthread_mutex_init(dead_lock, NULL);
	// pthread_mutex_init(meals_count_lock, NULL);
	//total_meals = 0;
	i = 0;
	while(i < amount_of_philos)
	{
		philo[i].thread_phil = thread[i];
		philo[i].food_lock = my_locks->food_lock;
		philo[i].print_lock = my_locks->print_lock;
		philo[i].dead_lock = my_locks->dead_lock;
		philo[i].meals_count_lock = my_locks->meals_count_lock;
		//philo[i].meals_total = &total_meals;
		philo[i].eating_round = 0;
		philo[i].in_degustation = 0;
		i++;
	}
	return(philo);
}

t_my_locks	*ft_create_my_locks()
{
	t_my_locks *my_locks;
	pthread_mutex_t *food_lock;
	pthread_mutex_t *print_lock;
	pthread_mutex_t *dead_lock;
	pthread_mutex_t *meals_count_lock;

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
