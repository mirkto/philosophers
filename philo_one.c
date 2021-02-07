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
	long		number_of_philosophers;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	long		number_of_times_each_philosopher_must_eat;
	long		timer;
	int			num;
	int			*status;
}				t_param;

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
	return (time_end - start_time);
}

long	stab_timer(long *timer, long time)
{
	long		save;
	long		now;
	long		need;
	
	save = time_now(*timer);
	need = save + (time / 1000);
	if (time != 0)
		usleep(time);
	now = time_now(*timer);
	if (need != now)
		timer += now - need;

	printf("|%li|\n", save);
	printf("|%li|\n", now);
	printf("|%li|\n", need);

	return (need);
}

void	*philo(void *tmp)
{
	t_param *all = tmp;
	int		philo_num;
	long	timer;

	philo_num = all->num++;
	printf("Philosopher %i is ready\n", philo_num);
	timer = time_start();
	printf("%i\n", all->status[philo_num - 1]);
	while (all->status[philo_num - 1] == 0)
	{
		printf("%li %i has taken a fork\n", stab_timer(&timer, 0), philo_num);

		printf("%li %i is eating\n", stab_timer(&timer, all->time_to_eat), philo_num);
		// usleep(all->time_to_eat);
		// stab_timer(all, all->time_to_eat);

		printf("%li %i is sleeping\n", stab_timer(&timer, all->time_to_sleep), philo_num);
		// usleep(all->time_to_sleep);
		// stab_timer(all, all->time_to_sleep);

		printf("%li %i is thinking\n", stab_timer(&timer, 0), philo_num);

		// printf("%li %i is died\n", time_now(all->timer), philo_num);
		all->status[philo_num - 1] = 1;
		// all->timer = stab_timer(&timer, 0);
	}
	// printf("Philosopher %i is died\n", philo_num);
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

void	print_param(t_param *all)
{
	printf("%li\n", all->number_of_philosophers);
	printf("%li\n", all->time_to_die);
	printf("%li\n", all->time_to_eat);
	printf("%li\n", all->time_to_sleep);
	printf("%li\n", all->number_of_times_each_philosopher_must_eat);
}

void	inits(t_param *all)
{
	int			status[all->number_of_philosophers];
	int			i;

	i = 0;
	while (i < all->number_of_philosophers)
	{
		status[i] = 0; 
		i++;
	}
	all->status = status;
	// i = -1;
	// while (++i < all->number_of_philosophers)
	// 	printf("%i\n", all->status[i]);
	pthread_mutex_init(&g_mutex, NULL);
	all->num = 1;
	all->timer = time_start();
}

void	init_philo(t_param *all)
{
	pthread_t	p[all->number_of_philosophers];
	int			i;

	i = 0;
	while (i < all->number_of_philosophers)
	{
		pthread_create(&p[i], NULL, philo, (void *)all);
		pthread_detach(p[i]);
		i++;
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
	print_param(&all);//--print from all
	inits(&all);
	init_philo(&all);
	//-----wait_philo----------
	// i = -1;
	// while (++i < all.number_of_philosophers)
	// 	pthread_join(p[i], NULL);
	//------while_of_death------
	while (1)
	{
		usleep(10000);
		i = 0;
		while (all.status[i])
		{
			if (all.status[i] == 1)
			{
				printf("%li %i is died\n", all.timer, i + 1);
				write(1, "Exit\n", 5);
				return (0);
			}
			i++;
		}

	}
	write(1, "BOOM!\n", 5);
	return (0);
}