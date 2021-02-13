/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngonzo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 16:15:14 by ngonzo            #+#    #+#             */
/*   Updated: 2021/02/13 16:15:15 by ngonzo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	take_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->left);
	pthread_mutex_lock(philo->right);
	check_and_print(philo, "has taken a fork 1");
	check_and_print(philo, "has taken a fork 2");
	philo->time_after_start_eat = time_now();
	check_and_print(philo, "is eating");
	time_work(philo->time_to_eat);
	pthread_mutex_unlock(philo->left);
	pthread_mutex_unlock(philo->right);
}

void	*philo_life(void *tmp)
{
	t_philo *philo;
	int i;

	i = 1;
	philo = (t_philo *)tmp;
	// printf("Philo name # %i\n", philo->philo_name);
	// while (i)
	// {
		take_fork(philo);
	// }
	return (0);
}