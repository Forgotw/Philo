/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 09:38:58 by lsohler@stu       #+#    #+#             */
/*   Updated: 2023/08/26 19:12:14 by lsohler          ###   ########.fr       */
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
			free(philo->meta);
			free(philo);
			break ;
		}
		free(philo);
		philo = tmp;
	}
}

void	sem_close_and_unlink(t_philo *philo)
{
	sem_close(philo->meta->forks);
	sem_close(philo->meta->print);
	sem_close(philo->meta->meal);
	sem_unlink("/philo_forks");
	sem_unlink("/philo_print");
	sem_unlink("/philo_meal");
}

void	free_and_join(t_philo *philo)
{
	int	status;

	waitpid(-1, &status, 0);
	while (philo)
	{
		kill(philo->pid, SIGKILL);
		philo = philo->right;
		if (philo->id == 1)
			break ;
	}
	sem_close_and_unlink(philo);
	free_lists(philo);
}
