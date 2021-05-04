#include "philo_three.h"

int		ft_inits(t_philo *philo)
{
	philo->philo_name = -1;
	philo->time_to_start_eat = -1;
	g_time_start = 0;
	sem_unlink("/print_sem");
	g_print_sem = sem_open("/print_sem", O_CREAT, S_IWUSR, 1);
	if (g_print_sem == SEM_FAILED)
		return (tl_perror("Error: system is not create print_sem"));
	sem_unlink("/fork_sem");
	g_fork_sem = sem_open("/fork_sem", O_CREAT, S_IWUSR, philo->num_of_philo);
	if (g_fork_sem == SEM_FAILED)
		return (tl_perror("Error: system is not create fork_sem"));
	return (0);
}
