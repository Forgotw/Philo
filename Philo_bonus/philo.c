/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 09:39:28 by lsohler@stu       #+#    #+#             */
/*   Updated: 2023/08/27 17:55:33 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_fork(t_philo *philo)
{
	sem_wait(philo->meta->forks);
	philo_print(philo, FORK);
	sem_wait(philo->meta->forks);
	philo_print(philo, FORK);
}

void	philo_eat(t_philo *philo)
{
	philo_fork(philo);
	sem_wait(philo->meta->meal);
	philo_print(philo, EAT);
	philo->meal += 1;
	philo->last_meal = get_time();
	sem_post(philo->meta->meal);
	ft_usleep(philo->meta->time_to_eat);
	sem_post(philo->meta->forks);
	sem_post(philo->meta->forks);
}

void	philo_after_meal(t_philo *philo)
{
	philo_print(philo, SLEEP);
	ft_usleep(philo->meta->time_to_sleep);
	philo_print(philo, THINK);
}

void	*routine(void *philosopher)
{
	t_philo	*philo;

	philo = (t_philo *)philosopher;
	pthread_create(&philo->tid, NULL, check_death, philosopher);
	if (philo->id % 2 == 0)
		ft_usleep(10);
	while (!check_death_m(philo))
	{
		philo_eat(philo);
		if (philo->meta->max_meal != -1
			&& philo->meal >= philo->meta->max_meal)
			break ;
		philo_after_meal(philo);
	}
	pthread_join(philo->tid, NULL);
	if (philo->meta->stop)
		exit(1);
	exit (0);
}

int	simulation(t_philo *philo)
{
	if (philo->meta->max_meal == 0)
		return (-1);
	philo->meta->start_time = get_time();
	while (philo)
	{
		philo->pid = fork();
		if (philo->pid < 0)
			return (-1);
		if (philo->pid == 0)
			routine(philo);
		philo = philo->right;
		if (philo->id == 1)
			break ;
	}
	free_and_join(philo);
	return (0);
}
