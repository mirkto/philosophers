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

#include "philo_two.h"

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
		philo[i].time_to_start_eat = -1;
	}
}

int		ft_inits(t_param *all, t_philo *philo)
{
	all->philo_threads = malloc(sizeof(pthread_t) * all->number_of_philo);
	if (!all->philo_threads)
		return (tl_perror("Error: malloc: inits philo_threads"));
	inits_philo(all, philo);
	g_time_start = 0;
	sem_unlink("/print_sem");
	g_print_sem = sem_open("/print_sem", O_CREAT, S_IWUSR, 1);
	if (g_print_sem == SEM_FAILED)
		return (tl_perror("Error: system is not create print_sem"));
	sem_unlink("/fork_sem");
	g_fork_sem = sem_open("/fork_sem", O_CREAT, S_IWUSR, all->number_of_philo);
	if (g_fork_sem == SEM_FAILED)
		return (tl_perror("Error: system is not create fork_sem"));
	return (0);
}
