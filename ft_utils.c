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

int		tl_perror(char *str)
{
	printf("%s\n", str);
	return (1);
}

int		tl_time_now(void)
{
	struct timeval	time_val;

	gettimeofday(&time_val, NULL);
	return (time_val.tv_sec * 1000 + time_val.tv_usec / 1000);
}

int		time_passed(void)
{
	int		time;

	time = tl_time_now() - g_time_start;
	if (time % 10 == 1)
		time--;
	return (time);
}

void	tl_check_and_print(t_philo *philo, char *str)
{
	pthread_mutex_lock(&g_print_mutex);
	if (g_exit_status == 0)
		printf("%i %i %s\n", time_passed(), philo->philo_name, str);
	pthread_mutex_unlock(&g_print_mutex);
}