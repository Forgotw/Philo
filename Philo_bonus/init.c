/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 09:39:45 by lsohler@stu       #+#    #+#             */
/*   Updated: 2023/08/26 20:04:08 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_semaphore(t_meta *meta)
{
	sem_unlink("/philo_forks");
	sem_unlink("/philo_meal");
	sem_unlink("/philo_print");
	meta->forks = sem_open("/philo_forks", O_CREAT
			| O_EXCL, 0666, meta->philo_n);
	meta->meal = sem_open("/philo_meal", O_CREAT | O_EXCL, 0666, 1);
	meta->print = sem_open("/philo_print", O_CREAT | O_EXCL, 0666, 1);
	if (meta->forks == SEM_FAILED
		|| meta->meal == SEM_FAILED
		|| meta->print == SEM_FAILED)
		return (-1);
	return (0);
}

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
	if (init_semaphore(meta))
		return (NULL);
	if (ac == 6)
		meta->max_meal = ft_atoi(av[5]);
	else
		meta->max_meal = -1;
	return (meta);
}

t_philo	*new_philo(t_meta *meta, int i)
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
	sem_unlink("/philo_counter");
	philo->counter = sem_open("/philo_counter", O_CREAT
			| O_EXCL, 0666, meta->philo_n);
	if (philo->counter == SEM_FAILED)
		return (NULL);
	return (philo);
}

t_philo	*init_philo(t_meta *meta)
{
	t_philo			*philo_start;
	t_philo			*philo;
	int				i;

	i = 1;
	philo = new_philo(meta, i);
	philo_start = philo;
	while (i++ < meta->philo_n)
	{
		philo->right = new_philo(meta, i);
		philo = philo->right;
	}
	philo->right = philo_start;
	return (philo_start);
}
