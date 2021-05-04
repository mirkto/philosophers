#include "philo_three.h"

int		check_valid_input(int argc, char **argv)
{
	int		arg;
	int		len;
	int		flag;

	if (argc < 5 || argc > 6)
		return (tl_perror("Error: Four or five argument only!"));
	flag = 0;
	arg = 0;
	while (++arg < argc)
	{
		len = -1;
		while (argv[arg][++len] != '\0' || argv[arg][0] == '\0')
			if (!('0' <= argv[arg][len] && argv[arg][len] <= '9') || len == 4)
			{
				printf("Error: Not valid argument %i\n", arg);
				flag = 1;
				break ;
			}
	}
	if (flag == 1)
		return (1);
	return (0);
}

int		ft_miniatoi(char *str)
{
	int		i;
	int		number;

	number = 0;
	i = -1;
	while (str[++i] != '\0')
		number = 10 * number + (str[i] - '0');
	return (number);
}

int		ft_parser(t_philo *philo, int argc, char **argv)
{
	if (check_valid_input(argc, argv))
		return (1);
	philo->num_of_philo = ft_miniatoi(argv[1]);
	philo->time_to_die = ft_miniatoi(argv[2]);
	philo->time_to_eat = ft_miniatoi(argv[3]);
	philo->time_to_sleep = ft_miniatoi(argv[4]);
	if (argc == 6)
		philo->num_of_each_must_eat = ft_miniatoi(argv[5]);
	else
		philo->num_of_each_must_eat = -1;
	if (philo->num_of_philo < 2 || philo->num_of_philo > 200)
		return (tl_perror("Error: Not valid number of philosophers"));
	if (philo->time_to_die < 60)
		return (tl_perror("Error: Not valid time_to_die"));
	if (philo->time_to_eat < 60)
		return (tl_perror("Error: Not valid time_to_eat"));
	if (philo->time_to_sleep < 60)
		return (tl_perror("Error: Not valid time_to_sleep"));
	return (0);
}
