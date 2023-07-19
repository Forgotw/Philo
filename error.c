/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 11:14:31 by lsohler           #+#    #+#             */
/*   Updated: 2023/07/19 12:23:46 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_arguments(int ac, char **av)
{
	int	i;

	i = 0;
	if (ac != 5 || ac != 6)
	{
		printf("Arguments count error\n");
		return (-1);
	}
	while (av++)
	{
		while (&av[i])
		{
			if (&av[i] < '0' || &av[i] > '9' || &av[i] == '-')
			{
				printf("Arguments error\n");
				return (-1);
			}
			i++;
		}
		i = 0;
	}
	return (0);
}
