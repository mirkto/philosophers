#include "philo_one.h"

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
	if (all->number_of_philosophers < 2 || all->number_of_philosophers > 200)
	{
		printf("Not valid number of philosophers\n");
		return (1);
	}
	return (0);
}