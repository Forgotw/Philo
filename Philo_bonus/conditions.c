/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conditions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler@student.42.fr <lsohler>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 12:06:37 by lsohler           #+#    #+#             */
/*   Updated: 2023/08/28 11:59:41 by lsohler@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death_m(t_philo *philo)
{
	int	ret;

	sem_wait(philo->meta->meal);
	if (philo->meta->stop)
		ret = 1;
	else
		ret = 0;
	sem_post(philo->meta->meal);
	return (ret);
}

void	*check_death(void *philovoid)
{
	t_philo	*philo;
	t_meta	*meta;

	philo = (t_philo *)philovoid;
	meta = philo->meta;
	while (1)
	{
		sem_wait(meta->meal);
		if (get_time() - philo->last_meal > meta->time_to_die)
		{
			philo_print(philo, DEAD);
			meta->stop = 1;
			sem_wait(meta->print);
			exit (1);
		}
		if (meta->stop)
			break ;
		if (meta->max_meal != -1
			&& philo->meal >= meta->max_meal)
			break ;
		sem_post(meta->meal);
	}
	sem_post(meta->meal);
	return (NULL);
}

// void	check_max_meal(t_philo *tmp)
// {
// 	sem_wait(tmp->meta->meal);
// 	while (tmp)
// 	{
// 		if (tmp->meal != tmp->meta->max_meal)
// 			break ;
// 		else
// 		{
// 			tmp = tmp->right;
// 			if (tmp->id == 1)
// 			{
// 				tmp->meta->all_ate = 1;
// 				break ;
// 			}
// 		}
// 	}
// 	sem_post(tmp->meta->meal);
// }

// void	*check_condition(void *philovoid)
// {
// 	t_philo	*philo;

// 	philo = (t_philo *)philovoid;
// 	while (!philo->meta->all_ate)
// 	{
// 		check_death(philo);
// 		if (philo->meta->stop)
// 			break ;
// 		if (philo->meta->max_meal != -1 && !philo->meta->stop)
// 			check_max_meal(philo);
// 	}
// 	return (NULL);
// }
