#include <unistd.h>//usleep
#include <stdlib.h>//atoi
#include <stdio.h>//printf
#include <pthread.h>
#include <sys/time.h>//gettimeofday

#include <string.h>//memset
#include <ctype.h>//isdigit

typedef struct	s_param
{
	long			number_of_philosophers;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			number_of_times_each_philosopher_must_eat;
	long			time_start;
	int				num;
	long			*philo_life_status;
	pthread_t		p_exit;
	pthread_t		p_time;
	int				exit_status;
	pthread_mutex_t	mutex_es;
	pthread_mutex_t	*mutex;
}					t_param;

typedef struct		s_philo
{
	int		num_phil;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		time_live;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
}					t_philo;

int		check_valid_input(int argc, char **argv);
int		parser(t_param *all, int argc, char **argv);
void	inits(t_param *all);
void	*p_exit(void *tmp);
void	init_fork(t_param *all);