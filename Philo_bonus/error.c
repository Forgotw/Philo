/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 11:14:31 by lsohler           #+#    #+#             */
/*   Updated: 2023/08/26 17:42:44 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_null_digit(char **av)
{
	int	i;
	int	s;

	i = 0;
	s = 1;
	while (av[s])
	{
		if (av[s][0] == '\0')
		{
			printf("Argument NULL\n");
			return (-1);
		}
		while (av[s][i])
		{
			if (av[s][i] < '0' || av[s][i] > '9' || av[s][i] == '-')
			{
				printf("Argument is not digit\n");
				return (-1);
			}
			i++;
		}
		i = 0;
		s++;
	}
	return (0);
}

int	check_arguments(int ac, char **av)
{
	int	i;
	int	s;

	i = 0;
	s = 1;
	if (ac < 5 || ac > 6)
	{
		printf("Argument count error\n");
		return (-1);
	}
	if (check_null_digit(av) == -1)
		return (-1);
	return (0);
}
