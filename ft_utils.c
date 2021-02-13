/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngonzo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 16:47:35 by ngonzo            #+#    #+#             */
/*   Updated: 2021/02/13 16:47:36 by ngonzo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int		ft_perror(char *str)
{
	printf("%s\n", str);
	return (1);
}

// int		ft_strlen(char *str)
// {
// 	int		i;

// 	i = 0;
// 	while (str[i])
// 		i++;
// 	return (i);
// }

int		time_now(void)
{
	struct timeval	time_val;

	gettimeofday(&time_val, NULL);
	return (time_val.tv_sec * 1000 + time_val.tv_usec / 1000);;
}

int		time_passed(void)
{
	int		time;

	time = time_now() - g_time_start;
	if (time % 10 == 1)
		time--;
	return(time);
}

void	time_work(int timer)
{
	int		start_time;

	start_time = time_now();
	usleep(timer * 1000 - 7000);
	while(time_now() - start_time < timer)
		usleep(100);
}

void	check_and_print(t_philo *philo, char *str)
{
	pthread_mutex_lock(&g_print_mutex);
	// if (all->exit_status == 0)
		printf("%i %i %s\n", time_passed(), philo->philo_name, str);
	pthread_mutex_unlock(&g_print_mutex);
}
