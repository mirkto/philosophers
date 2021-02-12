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

void	start_live(t_philo *philo, t_param *all)
{
	int i;

	i = 0;
	while (i < all->number_of_philo)
	{
		pthread_create(&all->philo_threads[i], NULL, philo_life, &philo[i]);
		usleep(50);
		i++;
	}
	
}

void	create_live(t_philo *philo, t_param all)
{
	int i;

	i = 0;
	while(i < all.number_of_philo)
	{
		philo[i].philo_name = i + 1;
		philo[i].time_to_die = all.time_to_die;
		philo[i].time_to_eat = all.time_to_eat;
		philo[i].time_to_sleep = all.time_to_sleep;
		philo[i].left = &all.fork_mutex[i];
		philo[i].right = &all.fork_mutex[(i + 1) % all.number_of_philo];
		i++;
	}
}

int		main(int argc, char **argv)
{
	t_param	all;
	t_philo *philo;

	if (check_valid_input(argc, argv))
		return (1);
	if (parser(&all, argc, argv))
		return (1);
	philo = malloc(sizeof(t_philo) * all.number_of_philo);
	if (inits(&all, philo))
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