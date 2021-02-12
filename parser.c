/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngonzo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 16:58:17 by ngonzo            #+#    #+#             */
/*   Updated: 2021/02/12 16:58:19 by ngonzo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int		check_valid_input(int argc, char **argv)
{
	int		arg;
	int		len;
	int		flag;

	if (argc < 5 || argc > 6)
		return (ft_perror("Four or five argument only!"));
	flag = 0;
	arg = 0;
	while (++arg < argc)
	{
		len = -1;
		while (argv[arg][++len] != '\0' || argv[arg][0] == '\0')
			if (!('0' <= argv[arg][len] && argv[arg][len] <= '9'))
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
	all->number_of_philo = ft_smatoi(argv[1]);
	all->time_to_die = ft_smatoi(argv[2]);
	all->time_to_eat = ft_smatoi(argv[3]);
	all->time_to_sleep = ft_smatoi(argv[4]);
	if (argc == 6)
		all->number_of_times_each_philo_must_eat = ft_smatoi(argv[5]);
	else
		all->number_of_times_each_philo_must_eat = -1;
	if (all->number_of_philo < 2 || all->number_of_philo > 200)
		return (ft_perror("Not valid number of philosophers"));
	return (0);
}
