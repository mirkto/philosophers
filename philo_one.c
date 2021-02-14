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

int		check_death(t_param *all, t_philo *philo)
{
	int		i;
	int		time_of_famine;

	while (1)
	{
		i = 0;
		while (i < all->number_of_philo)
		{
			time_of_famine = (int)(tl_time_now() - philo[i].time_to_start_eat);
			if (time_of_famine > all->time_to_die)
			{
				if (philo[i].num_of_each_must_eat == -1)
					tl_check_and_print(&philo[i], "dead");
				g_exit_status = 1;
				return (1);
			}
			i++;
		}
	}
	return (0);
}

int		start_live(t_philo *philo, t_param *all)
{
	int		i;

	g_time_start = tl_time_now();
	i = -1;
	while (++i < all->number_of_philo)
	{
		if (pthread_create(&all->philo_threads[i], NULL, ft_philo, &philo[i]))
			return (tl_perror("Error: System is not create philo_threads"));
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
		return (tl_perror("Error: Malloc: Inits philo structs"));
	if (ft_inits(&all, philo))
		return (1);
	start_live(philo, &all);
	check_death(&all, philo);
	wait_philo(&all);
	write(1, "Simulation is over\n", 19);
	return (0);
}
