/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 09:39:28 by lsohler@stu       #+#    #+#             */
/*   Updated: 2023/07/19 12:46:45 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_fork(t_philo *philo)
{

}

void	philo_eat(t_philo *philo)
{
	philo_fork(philo);
	pthread_mutex_lock(&philo->meta->meal_m);
	philo_print(philo, EAT);
}

void	philo_after_meal(t_philo *philo)
{

}

void	*routine(t_philo *philo)
{
	int	i;

	i = 0;
	if (philo->id % 2 == 0)
		ft_usleep(philo->meta->time_to_eat / 10);
	while (!philo->meta->stop)
	{
		philo_eat(philo);
		i++;
		philo->meal = i;
		if (philo->meal == philo->meta->max_meal)
			break ;
		philo_after_meal(philo);
	}
}

int	simulation(t_philo *philo)
{
	int	i;

	i = 0;
	if (philo->meta->max_meal == 0)
		return (-1);
	philo->meta->start_time = get_time();
	while (i < philo->meta->philo_n)
	{
		pthread_create(&philo->tid, NULL, &routine, &philo);
		philo = philo->right;
		i++;
	}
	check_condition(philo);
}