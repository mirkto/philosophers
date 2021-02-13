/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngonzo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 15:53:34 by ngonzo            #+#    #+#             */
/*   Updated: 2021/01/26 15:53:39 by ngonzo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int		start_live(t_philo *philo, t_param *all)
{
	int		i;

	g_time_start = tl_time_now();
	i = -1;
	while (++i < all->number_of_philo)
	{
		if (pthread_create(&all->philo_threads[i], NULL, ft_philo, &philo[i]))
			return (tl_perror("Error: system is not create philo_threads"));
		usleep(50);
	}
	return (0);
}

void	wait_philo(t_param *all)
{
	int		i;

	i = -1;
	while (++i < all->number_of_philo)
		pthread_join(all->philo_threads[i], NULL);
}

int		main(int argc, char **argv)
{
	t_param	all;
	t_philo	*philo;

	if (ft_parser(&all, argc, argv))
		return (1);
	philo = malloc(sizeof(t_philo) * all.number_of_philo);
	if (!philo)
		return (tl_perror("Error: malloc: inits philo structs"));
	if (ft_inits(&all, philo))
		return (1);
	start_live(philo, &all);
	wait_philo(&all);
	write(1, "BOOM!\n", 6);
	return (0);
}
