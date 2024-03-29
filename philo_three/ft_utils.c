#include "philo_three.h"

int		tl_perror(char *str)
{
	printf("%s\n", str);
	return (1);
}

long	tl_time_now(void)
{
	struct timeval	time_val;

	gettimeofday(&time_val, NULL);
	return (time_val.tv_sec * 1000 + time_val.tv_usec / 1000);
}

int		time_passed(void)
{
	int		time;

	time = (int)(tl_time_now() - g_time_start);
	if (time % 10 != 0)
		time -= time % 10;
	return (time);
}

void	tl_check_and_print(t_philo *philo, char *str)
{
	sem_wait(g_print_sem);
	if (str[0] == '*')
	{
		printf("%i %i %s\n", time_passed(), philo->philo_name, ++str);
		return ;
	}
	printf("%i %i %s\n", time_passed(), philo->philo_name, str);
	sem_post(g_print_sem);
}
