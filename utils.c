/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngonzo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 16:59:10 by ngonzo            #+#    #+#             */
/*   Updated: 2021/02/12 16:59:11 by ngonzo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"


int		ft_perror(char *str)
{
	printf("%s\n", str);
	return (1);
}

int		ft_strlen(char *str)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int		ft_smatoi(char *str)
{
	int		i;
	int		number;

	number = 0;
	i = -1;
	while(str[++i] != '\0')
		number = 10 * number + (str[i] - '0');
	return (number);
}