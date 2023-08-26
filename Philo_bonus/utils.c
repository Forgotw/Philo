/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 10:40:18 by lsohler@stu       #+#    #+#             */
/*   Updated: 2023/08/26 19:16:33 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	sign;
	int	result;
	int	i;

	result = 0;
	sign = 1;
	i = 0;
	while (str[i] && (str[i] == '\f' || str[i] == '\t' || str[i] == ' '
			|| str[i] == '\n' || str[i] == '\r' || str[i] == '\v'))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			sign = -1;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		result *= 10;
		result += str[i++] - '0';
	}
	result *= sign;
	return (result);
}

long long	get_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

int	ft_usleep(long long time)
{
	long long	start;

	start = get_time();
	while ((get_time() - start) < time)
	{
		usleep(5);
	}
	return (0);
}

long long	get_sim_time(long long start_time)
{
	struct timeval	current_time;
	long long		sim_time;

	gettimeofday(&current_time, NULL);
	sim_time = (current_time.tv_sec * 1000)
		+ (current_time.tv_usec / 1000) - start_time;
	return (sim_time);
}

/* printf(" \x1b[42m%i%s", philo->meal + 1, COLOR_RESET); */
void	philo_print(t_philo *philo, char *str)
{
	sem_wait(philo->meta->print);
	if (!philo->meta->stop)
	{
		printf("\x1b[40m%lli%s",
			get_sim_time(philo->meta->start_time), COLOR_RESET);
		printf(" \x1b[41m%i%s", philo->id, COLOR_RESET);
		printf("%s\n", str);
	}
	sem_post(philo->meta->print);
}
