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

// pthread_t		g_t1, g_t2;
pthread_t		g_p;
pthread_mutex_t	g_mutex;
struct timeval	g_tv1, g_tv2, g_dtv;
struct timezone	g_tz;

void	time_start()
{
	gettimeofday(&g_tv1, &g_tz);
}

long	time_stop()
{
	gettimeofday(&g_tv2, &g_tz);
	g_dtv.tv_sec = g_tv2.tv_sec - g_tv1.tv_sec;
	g_dtv.tv_usec = g_tv2.tv_usec - g_tv1.tv_usec;
	// if(g_dtv.tv_usec < 0)
	// {
	// 	g_dtv.tv_sec--;
	// 	g_dtv.tv_usec += 1000000;
	// }
	return (g_dtv.tv_sec * 1000 + g_dtv.tv_usec / 1000);
}

void	*philo(void *tmp)
{
	t_param *all = tmp;
	int			num;

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

int		main(int argc, char **argv)
{
	int		arg;
	int		len;
	int		num;
	t_param	all;
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
	time_start();
	all.num = 0;
	while (++all.num <= all.number_of_philosophers)
	{
		pthread_create(&g_p, NULL, philo, (void *)&all);
		usleep(1);
	}

	pthread_join(g_p, NULL);

	write(1, "Exit\n", 5);
	return (0);
}