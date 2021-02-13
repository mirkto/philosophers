/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_inits.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngonzo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 16:47:10 by ngonzo            #+#    #+#             */
/*   Updated: 2021/02/13 16:47:11 by ngonzo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	inits_philo(t_param *all, t_philo *philo)
{
	int i;

	i = -1;
	while (++i < all->number_of_philo)
	{
		philo[i].philo_name = i + 1;
		philo[i].time_to_die = all->time_to_die;
		philo[i].time_to_eat = all->time_to_eat;
		philo[i].time_to_sleep = all->time_to_sleep;
		philo[i].num_of_each_must_eat = all->number_of_times_each_must_eat;
		philo[i].left = &all->fork_mutex[i];
		philo[i].right = &all->fork_mutex[(i + 1) % all->number_of_philo];
		philo[i].time_to_start_eat = -1;
	}
}

int		init_fork(t_param *all)
{
	int			i;

	all->fork_mutex = malloc(sizeof(pthread_mutex_t) * all->number_of_philo);
	if (!all->fork_mutex)
		return (tl_perror("Error: malloc: inits fork_mutex"));
	i = -1;
	while (++i < all->number_of_philo)
		if (pthread_mutex_init(&all->fork_mutex[i], NULL))
			return (tl_perror("Error: system is not create fork_mutex"));
	return (0);
}

int		ft_inits(t_param *all, t_philo *philo)
{
	all->philo_threads = malloc(sizeof(pthread_t) * all->number_of_philo);
	if (!all->philo_threads)
		return (tl_perror("Error: malloc: inits philo_threads"));
	if (pthread_mutex_init(&g_print_mutex, NULL) != 0)
		return (tl_perror("Error: system is not create print_mutex"));
	if (init_fork(all) != 0)
		return (1);
	inits_philo(all, philo);
	g_time_start = 0;
	return (0);
}
