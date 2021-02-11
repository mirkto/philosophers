#include "philo_one.h"

void	inits(t_param *all)
{
	int			i;

	all->philo_life_status = (long *)malloc(sizeof(long) * all->number_of_philosophers);
	i = -1;
	while (++i < all->number_of_philosophers)
		all->philo_life_status[i] = 0; 
	pthread_mutex_init(&all->mutex_es, NULL);
	all->num = 1;
	all->exit_status = 0;
}

void	*p_exit(void *tmp)
{
	t_param	*all = tmp;
	int		i;
	long	time;

	while (1)
	{
		// time = sleep_and_time(all, 10000);
		// usleep(5000);
		// time = time_passed(all->time_start);
		i = 0;
		while (i < all->number_of_philosophers)
		{
			// printf("---| %li %li |---\n", (time_now() - all->philo_life_status[i]), all->time_to_die);

			// if ((time_now() - all->philo_life_status[i]) > all->time_to_die && all->philo_life_status[i] != 0)
			if (all->philo_life_status[i] == 0)
			{
				printf("%li %i is died\n", time, i + 1);
				write(1, "Exit\n", 5);
				return (0);
			}
			i++;
		}
	}
}