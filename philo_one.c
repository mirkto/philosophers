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

//-----------------------------
// isdigit
// atoi
// int		ft_strlen(char *str)
// {
// 	int		i;

// 	i = 0;
// 	while (str[i])
// 		i++;
// 	return (i);
// }
// //-----------------------------
// long	time_now()
// {
// 	struct timeval	tv;
// 	struct timezone	tz;

// 	gettimeofday(&tv, &tz);
// 	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
// }

// long	time_passed(long start_time)
// {
// 	return (time_now() - start_time);
// }

// void	check_exit_status_and_print(t_param *all, int num, long time, char *str)
// {
// 	pthread_mutex_lock(&all->mutex_es);
// 	if (all->exit_status == 0)
// 		printf("%li %i %s", time, num, str);
// 	pthread_mutex_unlock(&all->mutex_es);
// }

// void	monie(long timer)
// {
// 	long start_time;

// 	start_time = time_now();
// 	usleep(timer - 7000);
// 	printf("%ld\n", time_now() - start_time);
// 	while(time_now() - start_time < timer)
// 	{
// 		usleep(100);
// 	}
// 	printf("pozral\n");
// }

// void	*philo(void *tmp)
// {
// 	t_param *all;

// 	all = tmp;
// 	//all->
// }

// int	init_philo(t_param *all)
// {
// 	pthread_t	p[all->number_of_philosophers];
// 	int			i;

// 	i = 0;
// 	while (i < all->number_of_philosophers)
// 	{
// 		pthread_create(&p[i], NULL, philo, (void *)all) != 0;
// 		usleep(50);
// 		i++;
// 	}
// 	return (0);
// }

void	init_fork(t_param *all)
{
	int			i;

	all->mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * all->number_of_philosophers);
	i = 0;
	while (i < all->number_of_philosophers)
	{
		pthread_mutex_init(&all->mutex[i], NULL);
		i++;
	}
}


void	take_fork(t_philo *phil)
{
	pthread_mutex_lock(phil->left);
	phil_say(phil, "has taken a fork", 1); // функция которая говорит
	pthread_mutex_lock(phil->right);
	phil_say(phil, "has taken a fork", 1);
	phil->time_live = get_time(); //время когда он взял вилки < времени смерти
	phil_say(var, "is eating", 1);
	loop_time(var->eating);
	pthread_mutex_unlock(var->fork_l);
	pthread_mutex_unlock(var->fork_r);
}

void	philo(void *tmp)
{
	t_philo *philo;
	int i;

	i = 1;
	philo = (t_philo *)tmp;
	while (i)
	{
		take_fork()
	}
}

void	start_live(t_philo *philo, t_param all)
{
	int i;

	i = 0;
	while (i < all.number_of_philosophers)
	{
		pthread_create(&proces[i], NULL, philo, &philo[i]);
		usleep(50);
		i++;
	}
	
}

void	create_live(t_philo *philo, t_param all)
{
	int i;

	i = 0;
	while(i < all.number_of_philosophers)
	{
		philo[i].num_phil = i + 1;
		philo[i].time_to_die = all.time_to_die;
		philo[i].time_to_eat = all.time_to_eat;
		philo[i].time_to_sleep = all.time_to_sleep;
		philo[i].left = &all.mutex[i];
		philo[i].right = &all.mutex[(i + 1) % all.number_of_philosophers];
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
		return (0);
	inits(&all);
	init_fork(&all);
	philo = malloc(sizeof(t_philo) * all.number_of_philosophers);
	create_live(philo, all);
	start_live(philo, all);
	// all.time_start = time_now();
	// init_philo(&all);
	//------while_of_death------
	// pthread_create(&all.p_exit, NULL, p_exit, (void *)&all);
	// pthread_join(all.p_exit, NULL);
	write(1, "BOOM!\n", 6);
	return (0);
}