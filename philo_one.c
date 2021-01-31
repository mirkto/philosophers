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

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>//isdigit

typedef struct	s_param
{
	int			number_of_philosophers;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			number_of_times_each_philosopher_must_eat;
}				t_param;

int		main(int argc, char **argv)
{
	int		arg;
	int		len;
	t_param	all;

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
	printf("%i\n", all.number_of_philosophers);
	printf("%i\n", all.time_to_die);
	printf("%i\n", all.time_to_eat);
	printf("%i\n", all.time_to_sleep);
	printf("%i\n", all.number_of_times_each_philosopher_must_eat);
	return (0);
}