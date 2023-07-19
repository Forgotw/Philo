/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 09:34:52 by lsohler@stu       #+#    #+#             */
/*   Updated: 2023/07/19 15:58:38 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

# define DEAD "died"
# define EAT "is eating"
# define FORK "has taken a fork"
# define SLEEP "is sleeping"
# define THINK "is thinking"

typedef struct s_meta
{
	int				philo_n;
	long long		time_to_die;
	long long		time_to_sleep;
	long long		time_to_eat;
	int				max_meal;
	long long		start_time;
	int				stop;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	meal_m;
}				t_meta;

typedef struct s_philo
{
	int				id;
	pthread_t		tid;
	long long		last_meal;
	int				eating;
	int				meal;
	pthread_mutex_t	l_fork;
	pthread_mutex_t	r_fork;
	struct s_philo	*right;
	struct s_philo	*left;
	struct s_meta	*meta;
}				t_philo;

/*ERROR*/
int			check_arguments(int ac, char **av);
/*INIT*/
t_meta		*init_meta(int ac, char **av);
t_philo		*init_philo(t_meta *meta);
/*PHILO*/
void		check_condition(t_philo *philo);
int			simulation(t_philo *philo);
void		free_and_join(t_philo *philo);
/*UTILS*/
long long	get_time(void);
int			ft_usleep(long long time);
void		philo_print(t_philo *philo, char *str);
int			ft_atoi(const char *str);

#endif