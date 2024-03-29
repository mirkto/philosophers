#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct	s_param
{
	int				number_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_must_eat;
	pthread_t		*philo_threads;
	pthread_mutex_t	*fork_mutex;
}				t_param;

typedef struct	s_philo
{
	int				philo_name;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_each_must_eat;
	long			time_to_start_eat;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
}				t_philo;

pthread_mutex_t	g_print_mutex;
long			g_time_start;
int				g_exit_status;

int				ft_parser(t_param *all, int argc, char **argv);

int				ft_inits(t_param *all, t_philo *philo);

void			*ft_philo(void *tmp);

int				tl_perror(char *str);
long			tl_time_now();
void			tl_check_and_print(t_philo *philo, char *str);

#endif
