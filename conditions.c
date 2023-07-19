/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conditions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 12:06:37 by lsohler           #+#    #+#             */
/*   Updated: 2023/07/19 16:43:24 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_death(t_philo *philo)
{
	int		i;
	t_philo	*tmp;

	i = 0;
	tmp = philo;
	printf("check death\n");
	printf("tmp->meta->philo_n: %i\n", tmp->meta->philo_n);
	while (i < tmp->meta->philo_n)
	{
		printf("check death2\n");
		pthread_mutex_lock(&tmp->meta->meal_m);
		if (get_time() - tmp->last_meal > tmp->meta->time_to_eat)
		{
			printf("check death check if\n");
			philo_print(tmp, DEAD);
			tmp->meta->stop = 1;
			pthread_mutex_unlock(&tmp->meta->meal_m);
			return ;
		}
		printf("check death3\n");
		pthread_mutex_unlock(&tmp->meta->meal_m);
		tmp = tmp->right;
		i++;
		printf("check death4\n");
	}
	printf("check death fini\n");
}

void	check_max_meal(t_philo *philo)
{
	int		i;
	t_philo	*tmp;

	i = 0;
	tmp = philo;
	printf("check max meal\n");
	while (i < tmp->meta->philo_n)
	{
		printf("check max meal 1\n");
		if (tmp->meal == tmp->meta->max_meal)
			i++;
		else
			break ;
		tmp = tmp->right;
	}
	if (i == tmp->meta->philo_n)
		tmp->meta->stop = 1;
	else
		i = 0;
	printf("check max meal 2\n");
}

void	check_condition(t_philo *philo)
{
	while (!philo->meta->stop)
	{
		printf("check conditions\n");
		check_death(philo);
		printf("check conditions2222\n");
		if (philo->meta->max_meal != -1 && !philo->meta->stop)
			check_max_meal(philo);
		printf("check conditions3333\n");
	}
}