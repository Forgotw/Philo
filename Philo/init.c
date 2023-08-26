/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 09:39:45 by lsohler@stu       #+#    #+#             */
/*   Updated: 2023/07/25 19:04:40 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_meta	*init_meta(int ac, char **av)
{
	t_meta	*meta;

	meta = malloc(sizeof(t_meta));
	if (!meta)
		return (NULL);
	meta->philo_n = ft_atoi(av[1]);
	meta->time_to_die = ft_atoi(av[2]);
	meta->time_to_eat = ft_atoi(av[3]);
	meta->time_to_sleep = ft_atoi(av[4]);
	meta->stop = 0;
	meta->all_ate = 0;
	if (pthread_mutex_init(&meta->meal_m, NULL))
		return (NULL);
	if (pthread_mutex_init(&meta->print, NULL))
		return (NULL);
	if (ac == 6)
		meta->max_meal = ft_atoi(av[5]);
	else
		meta->max_meal = -1;
	return (meta);
}

pthread_mutex_t	*init_fork(t_meta *meta)
{
	pthread_mutex_t	*forks;
	int				i;

	i = 0;
	forks = malloc(sizeof (pthread_mutex_t) * meta->philo_n);
	if (!forks)
		return (NULL);
	while (i < meta->philo_n)
	{
		if (pthread_mutex_init(&forks[i], NULL))
			return (NULL);
		i++;
	}
	return (forks);
}

t_philo	*new_philo(t_meta *meta, pthread_mutex_t *forks, int i)
{
	t_philo	*philo;

	philo = malloc(sizeof (t_philo));
	if (!philo)
		return (NULL);
	philo->last_meal = get_time();
	philo->eating = 0;
	philo->id = i;
	philo->meal = 0;
	philo->meta = meta;
	if (i == 1)
		philo->l_fork = &forks[meta->philo_n - 1];
	else
		philo->l_fork = &forks[i - 2];
	philo->r_fork = &forks[i - 1];
	return (philo);
}

t_philo	*init_philo(t_meta *meta)
{
	t_philo			*philo_start;
	t_philo			*philo;
	int				i;

	i = 1;
	meta->forks = init_fork(meta);
	philo = new_philo(meta, meta->forks, i);
	philo_start = philo;
	while (i++ < meta->philo_n)
	{
		philo->right = new_philo(meta, meta->forks, i);
		philo = philo->right;
	}
	philo->right = philo_start;
	return (philo_start);
}
