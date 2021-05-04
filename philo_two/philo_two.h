#ifndef PHILO_TWO_H
# define PHILO_TWO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>

# define S_IWUSR 0000200
# define O_CREAT 0x0200

/*
** #include <sys/stat.h> S_IWUSR - Write for owner == #define S_IWUSR 0000200
** #include <fcntl.h> O_CREAT - create if nonexistant == #define O_CREAT 0x0200
*/

typedef struct	s_param
{
	int				number_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_must_eat;
	pthread_t		*philo_threads;
}				t_param;

typedef struct	s_philo
{
	int				philo_name;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_each_must_eat;
	long			time_to_start_eat;
}				t_philo;

sem_t			*g_print_sem;
sem_t			*g_fork_sem;
long			g_time_start;
int				g_exit_status;

int				ft_parser(t_param *all, int argc, char **argv);

int				ft_inits(t_param *all, t_philo *philo);

void			*ft_philo(void *tmp);

int				tl_perror(char *str);
long			tl_time_now();
void			tl_check_and_print(t_philo *philo, char *str);

#endif
