/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguede <aguede@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 18:27:29 by aguede            #+#    #+#             */
/*   Updated: 2023/10/25 18:56:52 by aguede           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <pthread.h>
# include <stdarg.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define TRUE 1
# define FALSE 0
# define E_TOOMUCHPHIL "Too much philosophers, use max 200\n"
# define E_NO_NEG_VAL "Your values can not be negative or 0\n"
# define E_WRONGINPUT "Input incorrect : -> subject"
# define E_NOVALIDNBR "only numbers brooo and no 0"

typedef struct s_philo
{
	int				amount;
	pthread_t		thread_phil;
	int				index;
	int				*dead;
	int				in_degustation;
	bool			full;
	int				eating_round;
	int				total_eating_round;
	int				*meals_total;
	size_t			last_meal_time;
	size_t			start_time;
	size_t			time_to_die;
	size_t			time_to_sleep;
	size_t			time_to_eat;
	pthread_mutex_t	*food_lock;
	pthread_mutex_t	*print_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meals_count_lock;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}					t_philo;

typedef struct s_my_locks
{
	pthread_mutex_t	*print_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*food_lock;
	pthread_mutex_t	*meals_count_lock;
}					t_my_locks;

void				ft_init_forks(pthread_mutex_t *fork, int amount,
						t_philo *philo);
t_philo				*ft_init_philos(pthread_mutex_t *forks, t_philo *philo,
						int argc, char **argv);
t_philo				*ft_init_philo_threads(t_philo *philo, pthread_t *thread,
						int amount_of_philos, t_my_locks *mylocks);
void				*ft_checker(void *param);
pthread_mutex_t		*ft_forks_creation(int i);
t_my_locks			*ft_create_my_locks(void);

void				ft_eat(t_philo *philo);
void				ft_sleep(t_philo *philo);
void				ft_think(t_philo *philo);
void				ft_die(t_philo *philo);
void				ft_threading(t_philo *philo, pthread_mutex_t *forks,
						t_my_locks *my_locks, pthread_t *threads);

pthread_t			*ft_create_threads(int amount);

void				ft_print_action(char *str, t_philo *philo);
int					ft_atoi(const char *str);
void				ft_error_message(char *str);
int					get_proper_time(void);
void				ft_usleep(size_t msec);
int					dead_or_alive(t_philo *philo);

void				ft_pjoin(t_philo *philo);

void				ft_destroy(t_philo *philo, pthread_mutex_t *forks,
						t_my_locks *my_locks, pthread_t *threads);

#endif
