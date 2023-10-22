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
	int i;

	i = 0;
	philo = NULL;
	threads = NULL;
	forks = NULL;
	if (argc != 5 && argc != 6)
		ft_error_message(E_WRONGINPUT);
	ft_check_arg(argc , argv);
	// il faudrait initialiser des mutexs dont je ne comprend pas l'utilite encore
	threads = ft_create_threads(ft_atoi(argv[1]));
	printf("threads created\n");
	forks = ft_forks_creation(ft_atoi(argv[1]));
	printf("forks created\n");
	philo = ft_init_philos(forks, philo, argc, argv);
	printf("philo initialized\n");
	philo = ft_init_philo_threads(philo, threads, ft_atoi(argv[1]));
	printf("philo's threads initialized\n");
	ft_init_forks(forks, ft_atoi(argv[1]), philo, argv);
	printf("forks initialized\n");
	printf("number of eating round : %d\n", philo->total_eating_round);
	printf("philo amount is %d\n", philo[0].amount);
	// printf("philo amount is %d\n", philo[1].amount);
	// printf("philo amount is %d\n", philo[2].amount);
	// printf("philo amount is %d\n", philo[3].amount);
	// printf("philo amount is %d\n", philo[4].amount);
	// printf("philo amount is %d\n", philo[5].amount);
	// printf("philo amount is %d\n", philo[6].amount);
	// printf("philo amount is %d\n", philo[7].amount);
	ft_threading(philo);
	printf("the threads ran like they should\n");
	// ft_pjoin(philo, threads);
	// ft_destroy(philo->amount, philo);
	//should I free the philo array and thread array ?
	return 0;
}