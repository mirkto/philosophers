#include <unistd.h>//usleep write
#include <stdlib.h>//malloc
#include <stdio.h>//printf
#include <pthread.h>
#include <sys/time.h>//gettimeofday

typedef struct	s_param
{
	int				number_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philo_must_eat;

	pthread_t		*philo_threads;
	// int				*philo_life_status;
	// pthread_t		p_exit;
	// pthread_t		p_time;
	int				exit_status;
	pthread_mutex_t	*fork_mutex;
}					t_param;

typedef struct		s_philo
{
	int				philo_name;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	// int				time;
	int				time_after_start_eat;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
}					t_philo;

pthread_mutex_t		g_print_mutex;
int					g_time_start;

int		check_valid_input(int argc, char **argv);
int		parser(t_param *all, int argc, char **argv);

int		ft_inits(t_param *all, t_philo *philo);

void	*philo_life(void *tmp);

int		ft_perror(char *str);
// int		ft_strlen(char *str);
int		time_now();
void	time_work(int timer);
void	check_and_print(t_philo *philo, char *str);


void	*p_exit(void *tmp);