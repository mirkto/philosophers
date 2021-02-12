/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_param.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngonzo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 16:58:01 by ngonzo            #+#    #+#             */
/*   Updated: 2021/02/12 16:58:04 by ngonzo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	create_live(t_philo *philo, t_param all)
{
	int i;

	i = -1;
	while(++i < all.number_of_philo)
	{
		philo[i].philo_name = i + 1;
		philo[i].time_to_die = all.time_to_die;
		philo[i].time_to_eat = all.time_to_eat;
		philo[i].time_to_sleep = all.time_to_sleep;
		philo[i].left = &all.fork_mutex[i];
		philo[i].right = &all.fork_mutex[(i + 1) % all.number_of_philo];
	}
}

int		init_fork(t_param *all)
{
	int			i;

	if (!(all->fork_mutex = malloc(sizeof(pthread_mutex_t) * all->number_of_philo)))
		return (ft_perror("Error: malloc: inits fork_mutex"));
	i = -1;
	while (++i < all->number_of_philo)
		if (pthread_mutex_init(&all->fork_mutex[i], NULL))
			return (ft_perror("Error: system is not create fork_mutex"));
	return (0);
}

int		ft_inits(t_param *all)
{
	if (!(all->philo_threads = malloc(sizeof(pthread_t) * all->number_of_philo)))
		return (ft_perror("Error: malloc: inits philo_threads"));
	if (pthread_mutex_init(&all->print_mutex, NULL) != 0)
		return (ft_perror("Error: system is not create print_mutex"));
	if (init_fork(all) != 0)
		return (1);
	all->exit_status = 0;
	return (0);
}

//----------------------------
// void	*p_exit(void *tmp)
// {
// 	t_param	*all = tmp;
// 	int		i;
// 	long	time;

// 	while (1)
// 	{
// 		// time = sleep_and_time(all, 10000);
// 		// usleep(5000);
// 		// time = time_passed(all->time_start);
// 		i = 0;
// 		while (i < all->number_of_philo)
// 		{
// 			// printf("---| %li %li |---\n", (time_now() - all->philo_life_status[i]), all->time_to_die);

// 			// if ((time_now() - all->philo_life_status[i]) > all->time_to_die && all->philo_life_status[i] != 0)
// 			if (all->philo_life_status[i] == 0)
// 			{
// 				printf("%li %i is died\n", time, i + 1);
// 				write(1, "Exit\n", 5);
// 				return (0);
// 			}
// 			i++;
// 		}
// 	}
// }
