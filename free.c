/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 09:38:58 by lsohler@stu       #+#    #+#             */
/*   Updated: 2023/07/19 15:21:01 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_lists(t_philo *philo)
{
	t_philo	*tmp;

	tmp = philo;
	free(philo->meta->forks);
	free(philo->meta);
	while (philo)
	{
		philo = philo->right;
		free(tmp);
		tmp = philo;
	}
}

void	free_and_join(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->meta->philo_n)
	{
		pthread_join(philo->tid, NULL);
		pthread_mutex_destroy(&philo->l_fork);
		pthread_mutex_destroy(&philo->r_fork);
		philo = philo->right;
		i++;
	}/*
	i = 0;
	while (i < philo->meta->philo_n)
	{
		i++;
	}*/
	pthread_mutex_destroy(&philo->meta->print);
	pthread_mutex_destroy(&philo->meta->meal_m);
	free_lists(philo);
}
