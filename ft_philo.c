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

void	time_work(int timer)
{
	int		start_time;

	start_time = tl_time_now();
	usleep(timer * 1000 - 7000);
	while (tl_time_now() - start_time < timer)
		usleep(100);
}

void	take_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->left);
	tl_check_and_print(philo, "has taken a fork");
	pthread_mutex_lock(philo->right);
	tl_check_and_print(philo, "has taken a fork");
	philo->time_to_start_eat = tl_time_now();
	tl_check_and_print(philo, "is eating");
	time_work(philo->time_to_eat);
	pthread_mutex_unlock(philo->left);
	pthread_mutex_unlock(philo->right);
}

void	*ft_philo(void *tmp)
{
	t_philo	*philo;

	philo = (t_philo *)tmp;
	while (philo->num_of_each_must_eat != 0)
	{
		take_fork(philo);
		tl_check_and_print(philo, "is sleeping");
		time_work(philo->time_to_sleep);
		tl_check_and_print(philo, "is thinking");
		if (philo->num_of_each_must_eat != -1)
			philo->num_of_each_must_eat--;
		if (philo->num_of_each_must_eat == 0)
			g_exit_status = 1;
		if (g_exit_status == 1)
			break ;
	}
	return (0);
}
