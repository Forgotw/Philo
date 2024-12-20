/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler@student.42.fr <lsohler>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 09:39:20 by lsohler@stu       #+#    #+#             */
/*   Updated: 2023/08/28 11:30:48 by lsohler@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <string.h>

void	print_philo(t_philo *data)
{
	t_philo	*philo;

	philo = data;
	while (philo)
	{
		printf("philo id: %i philo eat: %i\n", philo->id, philo->meal);
		printf("add: %p\n", &philo->meal);
		philo = philo->right;
		if (philo->id == 1)
			break ;
	}
}

int	main(int ac, char **av)
{
	t_meta	*meta;
	t_philo	*philo;

	if (!check_arguments(ac, av))
	{
		meta = init_meta(ac, av);
		philo = init_philo(meta);
		simulation(philo);
	}
}
