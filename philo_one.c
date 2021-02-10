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

#include <unistd.h>//usleep
#include <stdlib.h>//atoi
#include <stdio.h>//printf
#include <pthread.h>
#include <sys/time.h>//gettimeofday

#include <string.h>//memset
#include <ctype.h>//isdigit

typedef struct	s_param
{
	long			number_of_philosophers;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			number_of_times_each_philosopher_must_eat;
	long			time_start;
	int				num;
	int				*philo_life_status;
	pthread_t		p_exit;
	int				exit_status;
	pthread_mutex_t	mutex_es;
	pthread_mutex_t	*mutex;
}				t_param;

//-----------------------------
// isdigit
// atoi
int		ft_strlen(char *str)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
//-----------------------------
long	time_now()
{
	struct timeval	tv;
	struct timezone	tz;

	gettimeofday(&tv, &tz);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

long	time_passed(long start_time)
{
	long	time_end;

	time_end = time_now();
	return (time_end - start_time);
}

long	sleep_and_time(t_param *all, long time)
{
	long	now;

	usleep(time);
	now = time_passed(all->time_start);
	// printf("|%li|\n", now);
	// printf("|%li|\n", now % 10);
	return (now);
}

void	check_exit_status_and_print(t_param *all, int num, long time, char *str)
{
	pthread_mutex_lock(&all->mutex_es);
	if (all->exit_status == 0)
		printf("%li %i %s", time, num, str);
	pthread_mutex_unlock(&all->mutex_es);
}

void	*philo(void *tmp)
{
	t_param *all = tmp;
	int		philo_num;
	long	time;
	long	time_after_eat;
	pthread_mutex_t	*mutex_left_fork;
	pthread_mutex_t	*mutex_right_fork;

	time_after_eat = -1;
	philo_num = all->num++;
	// printf("Philosopher %i is ready\n", philo_num);//---
	mutex_left_fork = &all->mutex[philo_num - 1];
	mutex_right_fork = &all->mutex[philo_num % all->number_of_philosophers];
	while (all->exit_status == 0)
	{
		pthread_mutex_lock(mutex_left_fork);
		time = sleep_and_time(all, 0);
		check_exit_status_and_print(all, philo_num, time, "taken a fork\n");
		pthread_mutex_lock(mutex_right_fork);
		time = sleep_and_time(all, 0);
		check_exit_status_and_print(all, philo_num, time, "taken a fork\n");

		time = sleep_and_time(all, all->time_to_eat);
		check_exit_status_and_print(all, philo_num, time, "is eating\n");
		pthread_mutex_unlock(mutex_left_fork);
		pthread_mutex_unlock(mutex_right_fork);

		time = sleep_and_time(all, all->time_to_sleep);
		check_exit_status_and_print(all, philo_num, time, "is sleeping\n");

		time = sleep_and_time(all, 0);
		check_exit_status_and_print(all, philo_num, time, "is thinking\n");

		while (1)
		{
			all->time_to_die
		}

		pthread_mutex_lock(&all->mutex_es);
		if (all->exit_status == 0)
		{
			all->philo_life_status[philo_num - 1] = 1;
			all->exit_status = 1;
		}
		pthread_mutex_unlock(&all->mutex_es);
		// pthread_join(all->p_exit, NULL);
	}
	return (NULL);
}

int		check_valid_input(int argc, char **argv)
{
	int		arg;
	int		len;
	int		flag;

	if (argc < 5 || argc > 6)
	{
		printf("Four or five argument only!\n");
		return (1);
	}
	flag = 0;
	arg = 0;
	while (++arg < argc)
	{
		len = -1;
		while (argv[arg][++len] != '\0')
			if (isdigit(argv[arg][len]) == 0)
			{
				printf("Not valid argument %i\n", arg);
				flag = 1;
				break ;
			}
	}
	if (flag == 1)
		return (1);
	return (0);
}

int		parser(t_param *all, int argc, char **argv)
{
	all->number_of_philosophers = atoi(argv[1]);
	all->time_to_die = atoi(argv[2]) * 1000;
	all->time_to_eat = atoi(argv[3]) * 1000;
	all->time_to_sleep = atoi(argv[4]) * 1000;
	if (argc == 6)
		all->number_of_times_each_philosopher_must_eat = atoi(argv[5]);
	else
		all->number_of_times_each_philosopher_must_eat = -1;
	if (all->number_of_philosophers < 2 || all->number_of_philosophers > 200)
	{
		printf("Not valid number of philosophers\n");
		return (1);
	}
	return (0);
}

// void	print_param(t_param *all)
// {
// 	printf("%li\n", all->number_of_philosophers);
// 	printf("%li\n", all->time_to_die);
// 	printf("%li\n", all->time_to_eat);
// 	printf("%li\n", all->time_to_sleep);
// 	printf("%li\n", all->number_of_times_each_philosopher_must_eat);
// }

void	inits(t_param *all)
{
	int			i;

	all->philo_life_status = (int *)malloc(sizeof(int) * all->number_of_philosophers);
	i = -1;
	while (++i < all->number_of_philosophers)
		all->philo_life_status[i] = 0; 
	pthread_mutex_init(&all->mutex_es, NULL);
	all->num = 1;
	all->time_start = time_now();
	all->exit_status = 0;
}

int	init_philo(t_param *all)
{
	pthread_t	p[all->number_of_philosophers];
	// pthread_t	p;
	int			i;

	i = 0;
	while (i < all->number_of_philosophers)
	{
		// if (pthread_create(&p, NULL, philo, (void *)all) == 0)
		// 	pthread_detach(p);
		// else
		if (pthread_create(&p[i], NULL, philo, (void *)all) != 0)
		{
			printf("---|Alart|--- %d philo is not born! ---|Alart|---", i + 1);
			return (1);
		}
		usleep(50);//--time after born philo
		i++;
	}
	return (0);
}

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

void	*p_exit(void *tmp)
{
	t_param	*all = tmp;
	int		i;
	long	time;

	while (1)
	{
		// time = sleep_and_time(all, 10000);
		usleep(5000);
		time = time_passed(all->time_start);
		i = 0;
		while (i < all->number_of_philosophers)
		{
			if (all->philo_life_status[i] == 1)
			{
				printf("%li %i is died\n", time, i + 1);
				write(1, "Exit\n", 5);
				return (0);
			}
			i++;
		}
	}
}

int		main(int argc, char **argv)
{
	t_param	all;
	int		i;

	if (check_valid_input(argc, argv))
		return (1);
	if (parser(&all, argc, argv))
		return (0);
	// print_param(&all);//--print from all
	inits(&all);
	init_fork(&all);
	init_philo(&all);
	//-----wait_philo----------
	// i = -1;
	// while (++i < all.number_of_philosophers)
	// 	pthread_join(p[i], NULL);
	//------while_of_death------
	pthread_create(&all.p_exit, NULL, p_exit, (void *)&all);
	pthread_join(all.p_exit, NULL);
	write(1, "BOOM!\n", 6);
	return (0);
}