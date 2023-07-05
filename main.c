/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 09:39:20 by lsohler@stu       #+#    #+#             */
/*   Updated: 2023/07/05 12:51:11 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	routine(t_philo *philo)
{
	return (0);
}

int	simulation(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->meta->philo_n)
	{
		pthread_create(&philo->tid, NULL, &routine, &philo);
		philo = philo->right;
		i++;
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
