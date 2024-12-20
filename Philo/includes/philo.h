/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 09:34:52 by lsohler@stu       #+#    #+#             */
/*   Updated: 2023/07/25 19:04:21 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

# define DEAD "\x1B[31m died\x1B[0m"
# define EAT "\x1b[32m is eating\x1B[0m"
# define FORK "\x1b[33m has taken a fork\x1B[0m"
# define SLEEP "\x1b[34m is sleeping\x1B[0m"
# define THINK "\x1b[35m is thinking\x1B[0m"
# define COLOR_RESET "\x1B[0m"

typedef struct s_meta
{
	int				philo_n;
	long long		time_to_die;
	long long		time_to_sleep;
	long long		time_to_eat;
	int				max_meal;
	long long		start_time;
	int				stop;
	int				all_ate;
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
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	struct s_philo	*right;

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
int			check_death_m(t_philo *philo);
/*UTILS*/
long long	get_time(void);
int			ft_usleep(long long time);
void		philo_print(t_philo *philo, char *str);
int			ft_atoi(const char *str);
long long	get_sim_time(long long start_time);

#endif