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

typedef struct	s_param
{
	long		number_of_philosophers;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	long		number_of_times_each_philosopher_must_eat;
	long		timer;
}				t_param;

pthread_t		g_t1, g_t2;
pthread_t		g_p1, g_p2;
pthread_mutex_t	g_mutex;
t_param			all;

void	*print1(void *buf)
{
	int		i;
	char	c;

	c = '+';
	i = 0;
	// pthread_mutex_lock(&mutex);
	while (i < 5)
	{
		pthread_mutex_lock(&g_mutex);
		i++;
		printf("%i%c ", i, c);
		write(1, "/\\| ", 4);
		write(1, (char *)buf, strlen(buf));
		// usleep(100000);
		pthread_mutex_unlock(&g_mutex);
		usleep(1);
	}
	// pthread_mutex_unlock(&mutex);
	return (NULL);
}

void	*print2(void *buf)
{
	int		i;
	char	c;

	c = '-';
	i = 0;
	// pthread_mutex_lock(&mutex);
	while (i < 5)
	{
		pthread_mutex_lock(&g_mutex);
		i++;
		printf("%i%c ", i, c);
		write(1, "\\/| ", 4);
		write(1, (char *)buf, strlen(buf));
		// usleep(100000);
		pthread_mutex_unlock(&g_mutex);
		usleep(1);
	}
	// pthread_mutex_unlock(&mutex);
	return (NULL);
}

void	*philo(void *number)
{
	printf("%s Philosopher is ready\n", number);
	usleep(100);
	while (1)
	{
		// printf("Day %li:\n", timer);
		printf("day %li: ", all.timer);
		printf("Philosopher %s starts thinking\n", number);
		// while (1)
		// 	;
		usleep(100);
		printf("day %li: ", all.timer);
		printf("Philosopher %s finished thinking\n", number);

		printf("day %li: ", all.timer);
		printf("Philosopher %s starts eating\n", number);
		usleep(all.time_to_eat);
		// usleep(1000000);
		printf("day %li: ", all.timer);
		printf("Philosopher %s finished eating\n", number);

		printf("day %li: ", all.timer);
		printf("Philosopher %s starts sleeping\n", number);
		usleep(all.time_to_sleep);
		// usleep(1000000);
		printf("day %li: ", all.timer);
		printf("Philosopher %s finished sleeping\n", number);

		if (all.timer >= all.time_to_die)
		{
			printf("day %li: ", all.timer);
			printf("Philosopher %s died\n__--Game over--__\n", number);
			exit(1);
		}
		all.timer++;
	}
	return (NULL);
}

int		main(int argc, char **argv)
{
	int		arg;
	int		len;
	//--------check_param_number---------
	if (argc < 5 || argc > 6)
	{
		write(1, "four or five argument only!\n", 28);
		return (1);
	}
	//-----print_input_args-----
	// arg = 0;
	// while (argv[arg] != NULL)
	// {
	// 	len = 0;
	// 	while (argv[arg][len] != '\0')
	// 		len++;
	// 	write(1, argv[arg], len);
	// 	write(1, "\n", 1);
	// 	arg++;
	// }
	//--------check_param_valid---------
	arg = 0;
	while (++arg < argc)
	{
		len = -1;
		while (argv[arg][++len] != '\0')
			if (isdigit(argv[arg][len]) == 0)
			{
				printf("Not valid argument %i\n", arg);
				break ;
			}
	}
	//------inits_param------
	all.number_of_philosophers = atoi(argv[1]);
	all.time_to_die = atoi(argv[2]);
	all.time_to_eat = atoi(argv[3]);
	all.time_to_sleep = atoi(argv[4]);
	if (argc == 6)
		all.number_of_times_each_philosopher_must_eat = atoi(argv[5]);
	else
		all.number_of_times_each_philosopher_must_eat = -1;
	//-----param_print-----
	// printf("%i\n", all.number_of_philosophers);
	// printf("%i\n", all.time_to_die);
	// printf("%i\n", all.time_to_eat);
	// printf("%i\n", all.time_to_sleep);
	// printf("%i\n", all.number_of_times_each_philosopher_must_eat);
	//-----testing_str-------
	// char	*str1 = "1_1_1_1_1_\n";
	// char	*str2 = "_2_2_2_2_2\n";
	// //print((void *)str1);
	// //print((void *)str2);
	// pthread_mutex_init(&g_mutex, NULL);
	// // pthread_mutex_lock(&mutex);
	// // pthread_mutex_unlock(&mutex);
	// pthread_create(&g_t1, NULL, print1, (void *)str1);
	// usleep(1);
	// pthread_create(&g_t2, NULL, print2, (void *)str2);
	// // usleep(1000000);
	// pthread_join(g_t1, NULL);
	// pthread_join(g_t2, NULL);
	//--------philo-------------
	char	*str[2] = {"1", "2"};
	all.timer = 1;

	pthread_create(&g_p1, NULL, philo, (void *)str[0]);
	pthread_create(&g_p2, NULL, philo, (void *)str[1]);

	pthread_join(g_p1, NULL);
	pthread_join(g_p2, NULL);
	write(1, "Exit\n", 5);
	return (0);
}