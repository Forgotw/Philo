/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 09:34:52 by lsohler@stu       #+#    #+#             */
/*   Updated: 2023/07/05 14:07:29 by lsohler          ###   ########.fr       */
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
	int				philo_n;
	int				time_to_die;
	int				time_to_sleep;
	int				time_to_eat;
	int				max_meal;
	long long		start_time;
	int				dead;
	pthread_mutex_t	death;
}				t_meta;

typedef struct s_philo
{
	int				id;
	pthread_t		tid;
	long long		last_meal;
	int				eating;
	int				meal;
	pthread_mutex_t	meal_m;
	int				l_fork;
	int				r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	struct s_philo	*right;
	struct s_philo	*left;
	struct s_meta	*meta;
}				t_philo;

/*ERROR*/
int		check_arguments(int ac, char **av);
/*INIT*/
t_meta	*init_meta(int ac, char **av);
t_philo	*init_philo(t_meta *meta);
/*PHILO*/
#endif