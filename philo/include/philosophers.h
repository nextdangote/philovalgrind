
#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <string.h>
# include <stdbool.h>
# include <stdarg.h>
# include <sys/time.h>

#define TRUE 1
#define FALSE 0
#define E_TOOMUCHPHIL "Too much philosophers, use max 200\n"
#define E_NO_NEG_VAL "Your values can not be negative or 0\n"
#define E_WRONGINPUT "Your input is not correct, it should be that way :name of program, number of philosophers, time to die, time to eat, time to sleep, (amount of times each of them eat)\n"
#define E_NOVALIDNBR "You can only send numbers brooo and no 0 apart from the amount of times each of them eat\n"

typedef struct s_philo
{
    int amount;
    pthread_t   thread_phil;
    int index;
    int *dead;
    int in_degustation;
    bool    full;
    int eating_round;
    int  total_eating_round;
    int *meals_total;
    size_t  last_meal_time;
    size_t  start_time;
    size_t  time_to_die;
    size_t  time_to_sleep;
    size_t  time_to_eat;
    pthread_mutex_t *food_lock;
    pthread_mutex_t *print_lock;
    pthread_mutex_t *dead_lock;
    pthread_mutex_t *meals_count_lock;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
}   t_philo;

typedef struct s_my_locks
{
    pthread_mutex_t *print_lock;
    pthread_mutex_t *dead_lock;
    pthread_mutex_t *food_lock;
    pthread_mutex_t *meals_count_lock;
}   t_my_locks;

//initialization
void    ft_init_forks(pthread_mutex_t *fork, int amount, t_philo *philo);
t_philo *ft_init_philos(pthread_mutex_t *forks, t_philo *philo, int argc, char **argv);
t_philo	*ft_init_philo_threads(t_philo *philo, pthread_t *thread, int amount_of_philos, t_my_locks *mylocks);
void    *ft_checker(void *param);
pthread_mutex_t *ft_forks_creation(int i);
t_my_locks	*ft_create_my_locks();

//actions
void     ft_eat(t_philo *philo);
void     ft_sleep(t_philo *philo);
void     ft_think(t_philo *philo);
void     ft_die(t_philo *philo);
void    ft_threading(t_philo *philo);
pthread_t  *ft_create_threads(int amount);
// void	ft_init_threads(pthread_t *threads, t_philo *philo);

//utils
void    ft_print_action(char *str, t_philo *philo);
int     ft_atoi(const char *str);
void    ft_error_message(char *str);
int get_proper_time();
void ft_usleep(size_t msec);
int dead_or_alive(t_philo *philo);

//join
void ft_pjoin(t_philo *philo);

//free & destroy
void    ft_destroy(t_philo *philo, pthread_mutex_t *forks, t_my_locks *my_locks);

#endif
