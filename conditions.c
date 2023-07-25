/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conditions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 12:06:37 by lsohler           #+#    #+#             */
/*   Updated: 2023/07/25 19:04:01 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death_m(t_philo *philo)
{
	int	ret;

	pthread_mutex_lock(&philo->meta->meal_m);
	if (philo->meta->stop)
		ret = 1;
	else
		ret = 0;
	pthread_mutex_unlock(&philo->meta->meal_m);
	return (ret);
}

/* Printf pour le dernier repas*/
/* printf("Philo %i last meal at: %lli\n",
philo->id, get_sim_time(philo->meta->start_time) -
(get_time() - philo->last_meal)); */
void	check_death(t_philo *philo)
{
	while (philo)
	{
		pthread_mutex_lock(&philo->meta->meal_m);
		if (get_time() - philo->last_meal > philo->meta->time_to_die)
		{
			philo_print(philo, DEAD);
			pthread_mutex_lock(&philo->meta->print);
			philo->meta->stop = 1;
			pthread_mutex_unlock(&philo->meta->print);
		}
		pthread_mutex_unlock(&philo->meta->meal_m);
		if (philo->meta->stop)
			break ;
		philo = philo->right;
		if (philo->id == 1)
			break ;
	}
}

void	check_max_meal(t_philo *tmp)
{
	pthread_mutex_lock(&tmp->meta->meal_m);
	while (tmp)
	{
		if (tmp->meal != tmp->meta->max_meal)
			break ;
		else
		{
			tmp = tmp->right;
			if (tmp->id == 1)
			{
				tmp->meta->all_ate = 1;
				break ;
			}
		}
	}
	pthread_mutex_unlock(&tmp->meta->meal_m);
}

void	check_condition(t_philo *philo)
{
	while (!philo->meta->all_ate)
	{
		check_death(philo);
		if (philo->meta->stop)
			break ;
		if (philo->meta->max_meal != -1 && !philo->meta->stop)
			check_max_meal(philo);
	}
}
