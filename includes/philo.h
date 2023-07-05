/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler@student.42.fr <lsohler>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 09:34:52 by lsohler@stu       #+#    #+#             */
/*   Updated: 2023/07/04 13:55:40 by lsohler@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_meta
{
	int	philo_n;
	int	time_to_die;
	int	time_to_sleep;
	int	time_to_eat;
	int	max_meal;
	int	death;
}				t_meta;

typedef struct s_philo
{
	int				id;
	int				ate;
	int				eating;
	int				meal;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	struct s_philo	*right;
	struct s_philo	*left;
	struct t_meta	*meta;
}				t_philo;


#endif