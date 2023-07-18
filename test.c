/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler@student.42.fr <lsohler>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 13:58:44 by lsohler           #+#    #+#             */
/*   Updated: 2023/07/14 11:20:12 by lsohler@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct s_meta
{
	pthread_mutex_t	x;
	int				tab[2];
	int				i;
}				t_meta;

typedef struct s_philo
{
	pthread_t		tid;
	char			*name;
	struct s_meta	*meta;
}				t_philo;

void	*routine(void *arg)
{
	t_philo *philo;

	philo = arg;
	//printf("test: %s: Tab[0]: %i Tab[1]: %i\n", philo->name, philo->meta->tab[0], philo->meta->tab[1]);
	while (philo->meta->i <= 10)
	{
		//printf("%s: Tab[0]: %i Tab[1]: %i, i: %i\n", philo->name, philo->meta->tab[0], philo->meta->tab[1], philo->meta->i);
		if (philo->meta->tab[0] == 1)
		{
			pthread_mutex_lock(&philo->meta->x);
			printf("%s: grab the forks\n", philo->name);
			philo->meta->tab[0] = 0;
			philo->meta->tab[1] = 0;
			usleep(500000);
			pthread_mutex_unlock(&philo->meta->x);
			printf("%s: finished eating is now sleeping\n", philo->name);
			//printf("%s: Tab[0]: %i Tab[1]: %i, i: %i mutex locked\n", philo->name, philo->meta->tab[0], philo->meta->tab[1], philo->meta->i);
			philo->meta->tab[0] = 1;
			philo->meta->tab[1] = 1;
			//printf("%s: Tab[0]: %i Tab[1]: %i, i: %i mutex unlocked\n", philo->name, philo->meta->tab[0], philo->meta->tab[1], philo->meta->i);
			usleep(500000);
			printf("%s: finished sleeping\n", philo->name);
			philo->meta->i++;
		}
		else if (philo->meta->tab[0] == 0)
		{
			//pthread_mutex_unlock(&philo->meta->x);
			printf("%s: is waiting for the forks\n", philo->name);
			usleep(500000 / 3);
		}
	}
	return (NULL);
}

int	main(void)
{
	t_meta		*meta;
	t_philo		*one;
	t_philo		*two;

	meta = malloc(sizeof(t_meta));
	meta->tab[0] = 1;
	meta->tab[1] = 1;
	meta->i = 0;
	pthread_mutex_init(&meta->x, NULL);
	// one.name = malloc(sizeof(char) * strlen("Philo_x"));
	one = malloc(sizeof(t_philo));
	two = malloc(sizeof(t_philo));
	one->name = "Philo_1";
	two->name = "Philo_2";
	one->meta = meta;
	two->meta = meta;
	pthread_create(&one->tid, NULL, &routine, one);
	usleep(400);
	pthread_create(&two->tid, NULL, &routine, two);
	printf("TEST TEST TEST TEST\nTEST TEST TEST TEST\nTEST TEST TEST TEST\n");
	pthread_join(one->tid, NULL);
	pthread_join(two->tid, NULL);
	pthread_mutex_destroy(&meta->x);
	return (0);
}
