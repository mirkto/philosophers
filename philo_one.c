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
#include <ctype.h>//isdigit
#include <pthread.h>
#include <string.h>//memset
#include <sys/time.h>//gettimeofday

typedef struct	s_param
{
	long		number_of_philosophers;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	long		number_of_times_each_philosopher_must_eat;
	long		timer;
	int			num;
}				t_param;

pthread_t		g_p;
pthread_mutex_t	g_mutex;

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
long	time_start()
{
	struct timeval	tv;
	struct timezone	tz;

	gettimeofday(&tv, &tz);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

long	time_now(long start_time)
{
	long	time_end;

	time_end = time_start();
	return (start_time - time_end);
}

void	*philo(void *tmp)
{
	t_param *all = tmp;
	int		num;

	num = all->num;
	printf("Philosopher %i is ready\n", num);
	// usleep(100);
	while (1)
	{
		// printf("%li %i has taken a fork", );

		// printf("%li %i is eating", );
		// usleep(all->time_to_eat);

		// printf("%li %i is sleeping", );
		// usleep(all.time_to_sleep);

		// printf("%li %i is thinking", );

		// printf("%li %i is died", );
		break ;
	}
	printf("Philosopher %i is died\n", num);
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
	all->time_to_die = atoi(argv[2]);
	all->time_to_eat = atoi(argv[3]);
	all->time_to_sleep = atoi(argv[4]);
	if (argc == 6)
		all->number_of_times_each_philosopher_must_eat = atoi(argv[5]);
	else
		all->number_of_times_each_philosopher_must_eat = -1;
	if (all->number_of_philosophers == 1)
	{
		printf("000 1 has taken a fork\n");
		printf("%li 1 dead\n", all->time_to_die);
		return (1);
	}
	return (0);
}

void	print_param(t_param *all)
{
	printf("%li\n", all->number_of_philosophers);
	printf("%li\n", all->time_to_die);
	printf("%li\n", all->time_to_eat);
	printf("%li\n", all->time_to_sleep);
	printf("%li\n", all->number_of_times_each_philosopher_must_eat);
}

int		main(int argc, char **argv)
{
	t_param	all;

	if (check_valid_input(argc, argv))
		return (1);
	if (parser(&all, argc, argv))
		return (0);
	print_param(&all);
	//--------philo-------------
	// time_start();
	// all.num = 0;
	// while (++all.num <= all.number_of_philosophers)
	// {
	// 	pthread_create(&g_p, NULL, philo, (void *)&all);
	// 	usleep(1);
	// }
	// pthread_join(g_p, NULL);
	write(1, "Exit\n", 5);
	return (0);
}