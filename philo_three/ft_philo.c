#include "philo_three.h"

void	time_work(int timer)
{
	long	start_time;

	start_time = tl_time_now();
	usleep(timer * 1000 - 7000);
	while (tl_time_now() - start_time < timer)
		usleep(100);
}

void	take_fork(t_philo *philo)
{
	sem_wait(g_fork_sem);
	sem_wait(g_fork_sem);
	tl_check_and_print(philo, "has taken a fork");
	tl_check_and_print(philo, "has taken a fork");
	philo->time_to_start_eat = tl_time_now();
	tl_check_and_print(philo, "is eating");
	time_work(philo->time_to_eat);
	sem_post(g_fork_sem);
	sem_post(g_fork_sem);
}

void	*ft_philo(void *tmp)
{
	t_philo	*philo;

	philo = (t_philo *)tmp;
	philo->time_to_start_eat = tl_time_now();
	while (philo->num_of_each_must_eat != 0)
	{
		take_fork(philo);
		tl_check_and_print(philo, "is sleeping");
		time_work(philo->time_to_sleep);
		tl_check_and_print(philo, "is thinking");
		if (philo->num_of_each_must_eat != -1)
			philo->num_of_each_must_eat--;
		if (philo->num_of_each_must_eat == 0)
		{
			sem_wait(g_print_sem);
			exit(0);
		}
	}
	return (0);
}
