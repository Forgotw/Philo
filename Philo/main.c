/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 09:39:20 by lsohler@stu       #+#    #+#             */
/*   Updated: 2023/08/27 19:35:22 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_philo(t_philo *data)
{
	t_philo	*philo;

	philo = data;
	while (philo)
	{
		printf("philo id: %i philo eat: %i\n", philo->id, philo->meal);
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
/*void	*routine_one(void *philosopher)
{
	t_philo	*philo;

	philo = (t_philo *)philosopher;
	pthread_mutex_lock(philo->l_fork);
	philo_print(philo, FORK);
	ft_usleep(philo->meta->time_to_die);
	philo_print(philo, DEAD);
}

void	one_philo(t_philo *philo)
{
	printf("test\n");
	pthread_create(&philo->tid, NULL, routine_one, (void *)philo);
	free_and_join(philo);
}

int	main(int ac, char **av)
{
	t_meta	*meta;
	t_philo	*philo;

	if (!check_arguments(ac, av))
	{
		meta = init_meta(ac, av);
		philo = init_philo(meta);
		if (philo->meta->philo_n == 1)
			one_philo(philo);
		else
			simulation(philo);
	}
}*/