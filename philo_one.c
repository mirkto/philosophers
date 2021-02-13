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
	int i;

	g_time_start = time_now();
	i = -1;
	while (++i < all->number_of_philo)
	{
		if (pthread_create(&all->philo_threads[i], NULL, philo_life, &philo[i]) != 0)
			return (ft_perror("Error: system is not create philo_threads"));
		usleep(50);
	}
	return (0);
}

int		main(int argc, char **argv)
{
	t_param	all;
	t_philo *philo;

	if (check_valid_input(argc, argv))
		return (1);
	if (parser(&all, argc, argv))
		return (1);
	if (!(philo = malloc(sizeof(t_philo) * all.number_of_philo)))
		return (ft_perror("Error: malloc: inits philo structs"));
	if (ft_inits(&all, philo))
		return (1);

	start_live(philo, &all);
	// init_philo(&all);
	//------while_of_death------
	// pthread_create(&all.p_exit, NULL, p_exit, (void *)&all);
	// pthread_join(all.p_exit, NULL);
	//-------wait_philo
	int	i = -1;
	while (++i < all.number_of_philo)
		pthread_join(all.philo_threads[i], NULL);
	//-------
	write(1, "BOOM!\n", 6);
	return (0);
}