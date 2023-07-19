/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 09:39:28 by lsohler@stu       #+#    #+#             */
/*   Updated: 2023/07/19 16:41:00 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_fork(t_philo *philo)
{
	printf("test philo fork\n");
	pthread_mutex_lock(&philo->l_fork);
	philo_print(philo, FORK);
	pthread_mutex_lock(&philo->r_fork);
	philo_print(philo, FORK);
}

void	philo_eat(t_philo *philo)
{
	printf("test philo eat\n");
	philo_fork(philo);
	pthread_mutex_lock(&philo->meta->meal_m);
	philo_print(philo, EAT);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->meta->meal_m);
	ft_usleep(philo->meta->time_to_eat);
	pthread_mutex_unlock(&philo->l_fork);
	pthread_mutex_unlock(&philo->r_fork);
}

void	philo_after_meal(t_philo *philo)
{
	printf("test philo after meal\n");
	philo_print(philo, SLEEP);
	ft_usleep(philo->meta->time_to_sleep);
	philo_print(philo, THINK);
}

void	*routine(void *philosopher)
{
	t_philo	*philo;

	philo = (t_philo *)philosopher;
	if (philo->id % 2 == 0)
	{
		ft_usleep(philo->meta->time_to_eat / 10);
	}
	while (!philo->meta->stop)
	{
		philo_eat(philo);
		philo->meal += 1;
		if (philo->meal == philo->meta->max_meal || philo->meta->stop)
			break ;
		philo_after_meal(philo);
	}
	return (NULL);
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
		pthread_create(&philo->tid, NULL, routine, (void *)philo);
		philo = philo->right;
		i++;
	}
	check_condition(philo);
	free_and_join(philo);
	return (0);
}