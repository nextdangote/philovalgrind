#include "../include/philosophers.h"

void    ft_check_arg_for_6(char **argv, int argc)
{
	int i;

	i = 1;
	while(i < argc)
	{
		if(!ft_atoi((const char *)argv[i]))
			ft_error_message(E_NOVALIDNBR);
		i++;
	}
	i = 1;
	while(i < argc + 1)
	{
		if(ft_atoi((const char *)argv[i]) <= 0)
			ft_error_message(E_NO_NEG_VAL);
		i++;
	}
	if(ft_atoi((const char *)argv[1]) > 200)
		ft_error_message(E_TOOMUCHPHIL);
	printf("check with number of eating rounds\n");
}

int    ft_check_arg(int argc, char **argv)
{
	int i;

	i = 1;
	if (argc == 6)
		ft_check_arg_for_6(argv, argc - 1);
	else
	{
		while(i < argc)
		{
			if(!ft_atoi((const char *)argv[i]))
				ft_error_message(E_NOVALIDNBR);
			i++;
		}
		i = 1;
		while(i < argc)
		{
			if(ft_atoi((const char *)argv[i]) <= 0)
				ft_error_message(E_NO_NEG_VAL);
			i++;
		}
		if(ft_atoi((const char *)argv[1]) > 200)
			ft_error_message(E_TOOMUCHPHIL);
		printf("check without eating rounds\n");
	}
	return(1);
}

int main(int argc, char **argv)
{
	t_philo   *philo;
	pthread_t *threads;
	pthread_mutex_t *forks;
	t_my_locks	*my_locks;

	philo = NULL;
	threads = NULL;
	forks = NULL;
	my_locks = NULL;
	if (argc != 5 && argc != 6)
		ft_error_message(E_WRONGINPUT);
	ft_check_arg(argc , argv);
	threads = ft_create_threads(ft_atoi(argv[1]));
	forks = ft_forks_creation(ft_atoi(argv[1]));
	printf("forks are initialized\n");
	my_locks = ft_create_my_locks();
	printf("locks are initialized\n");
	// (void)threads;
	// (void)philo;
	// (void)my_locks;
	// (void)forks;
	philo = ft_init_philos(forks, philo, argc, argv);
	philo = ft_init_philo_threads(philo, threads, ft_atoi(argv[1]), my_locks);
	ft_init_forks(forks, ft_atoi(argv[1]), philo);
	ft_threading(philo);
	ft_destroy(philo, forks, my_locks);
	return 0;
}