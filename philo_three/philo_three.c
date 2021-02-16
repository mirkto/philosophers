/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngonzo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 17:37:31 by ngonzo            #+#    #+#             */
/*   Updated: 2021/02/16 17:37:34 by ngonzo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	*check_death(void *tmp)
{
	t_philo	*philo;
	int		time_of_famine;

	philo = (t_philo *)tmp;
	while (1)
	{
		time_of_famine = (int)(tl_time_now() - philo->time_to_start_eat);
		if (time_of_famine > philo->time_to_die)
		{
			if (philo->num_of_each_must_eat != 0)
				tl_check_and_print(philo, "*dead");
			break ;
		}
	}
	exit(0);
}

void	wait_philo(t_philo *philo, int pid[])
{
	int		i;

	waitpid(-1, NULL, 0);
	if (philo->num_of_each_must_eat != 0)
	{
		i = -1;
		while (++i < philo->num_of_philo)
			kill(pid[i], SIGKILL);
	}
	else
	{
		i = -1;
		while (++i < philo->num_of_philo)
			waitpid(-1, NULL, 0);
	}
	sem_close(g_print_sem);
	sem_unlink("/print_sem");
	sem_close(g_fork_sem);
	sem_unlink("/fork_sem");
}

int		start_live(t_philo *philo, pthread_t *p_check_death)
{
	int		i;
	int		pid[philo->num_of_philo];

	g_time_start = tl_time_now();
	i = -1;
	while (++i < philo->num_of_philo)
	{
		philo->philo_name = i + 1;
		pid[i] = fork();
		if (pid[i] == 0)
		{
			pthread_create(p_check_death, NULL, check_death, philo);
			pthread_detach(*p_check_death);
			ft_philo(philo);
			exit(0);
		}
		usleep(50);
	}
	wait_philo(philo, pid);
	return (0);
}

int		main(int argc, char **argv)
{
	t_philo		philo;
	pthread_t	p_check_death;

	if (ft_parser(&philo, argc, argv))
		return (1);
	if (ft_inits(&philo))
		return (1);
	start_live(&philo, &p_check_death);
	write(1, "Simulation is over\n", 19);
	return (0);
}
