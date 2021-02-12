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

void	take_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->left);
	// phil_say(phil, "has taken a fork", 1); // функция которая говорит
	pthread_mutex_lock(philo->right);
	// phil_say(phil, "has taken a fork", 1);
	// phil->time_after_start_eat = get_time(); //время когда он взял вилки < времени смерти
	printf("Philo %i taken a fork\n", philo->philo_name);
	// phil_say(phil, "is eating", 1);
	// loop_time(phil->time_to_eat);
	pthread_mutex_unlock(philo->left);
	pthread_mutex_unlock(philo->right);
}

void	*philo_life(void *tmp)
{
	t_philo *philo;
	int i;

	i = 1;
	philo = (t_philo *)tmp;
	printf("Philo name # %i\n", philo->philo_name);
	// while (i)
	// {
		take_fork(philo);
	// }
	return (0);
}

int		start_live(t_philo *philo, t_param *all)
{
	int i;

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
	if (ft_inits(&all))
		return (1);

	create_live(philo, all);
	start_live(philo, &all);
	// all.time_start = time_now();
	// init_philo(&all);
	//------while_of_death------
	// pthread_create(&all.p_exit, NULL, p_exit, (void *)&all);
	// pthread_join(all.p_exit, NULL);
	write(1, "BOOM!\n", 6);
	return (0);
}