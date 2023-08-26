/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 09:38:58 by lsohler@stu       #+#    #+#             */
/*   Updated: 2023/07/25 15:12:34 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_lists(t_philo *philo)
{
	t_philo	*tmp;

	tmp = philo;
	while (philo)
	{
		tmp = philo->right;
		if (philo->id == philo->meta->philo_n)
		{
			free(philo->meta->forks);
			free(philo->meta);
			free(philo);
			break ;
		}
		free(philo);
		philo = tmp;
	}
}

void	free_and_join(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->meta->philo_n)
	{
		pthread_join(philo->tid, NULL);
		pthread_mutex_destroy(&philo->meta->forks[i]);
		philo = philo->right;
		i++;
	}
	pthread_mutex_destroy(&philo->meta->print);
	pthread_mutex_destroy(&philo->meta->meal_m);
	free_lists(philo);
}
