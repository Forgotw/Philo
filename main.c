/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 09:39:20 by lsohler@stu       #+#    #+#             */
/*   Updated: 2023/07/18 14:57:24 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_condition(t_philo *philo)
{
	t_philo	*tmp;
	int		i;

	i = 0;
	tmp = philo;
	while (!tmp->meta->stop)
	{
		while (i < tmp->meta->philo_n)
		{
			pthread_mutex_lock(&tmp->meta->meal_m);
			if (get_time() - tmp->last_meal > tmp->meta->time_to_eat)
			{
				philo_print(tmp, DEAD);
				tmp->meta->stop = 1;
				return (NULL);
			}
			pthread_mutex_unlock(&tmp->meta->meal_m);
			tmp = tmp->right;
			i++;
		}
		while (i < tmp->meta->philo_n)
		{
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
	}
}

void	*routine(t_philo *philo)
{
	int	i;

	i = 0;
	if (philo->id % 2 == 0)
		ft_usleep(philo->meta->time_to_eat / 10);
	while (!philo->meta->stop)
	{
		if (philo->meal > 0)
			philo_after_meal(philo);
		philo_eat(philo);
		i++;
		philo->meal = i;
		if (philo->meta->max_meal != -1 && philo->meal == philo->meta->max_meal)
			break ;
	}
	return (0);
}

int	simulation(t_philo *philo)
{
	int	i;

	i = 0;
	philo->meta->start_time = get_time();
	while (i < philo->meta->philo_n)
	{
		pthread_create(&philo->tid, NULL, &routine, &philo);
		philo = philo->right;
		i++;
	}
	check_condition(philo);
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
