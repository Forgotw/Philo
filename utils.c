/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 10:40:18 by lsohler@stu       #+#    #+#             */
/*   Updated: 2023/07/19 13:32:35 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

int	ft_usleep(useconds_t time)
{
	u_int64_t	start;
	start = get_time();
	while ((get_time() - start) < time)
		usleep(time / 10);
	return(0);
}

long long	get_sim_time(long long start_time)
{
	struct timeval	current_time;
	long long		sim_time;

	gettimeofday(&current_time, NULL);
	sim_time = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000) - start_time;
	return (sim_time);
}

void	philo_print(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->meta->print);
	if (!philo->meta->stop)
	{
		printf("%lli %i %s\n", get_sim_time(philo->meta->start_time), philo->id, str);
	}
}