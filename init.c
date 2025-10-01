/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gifanell <gifanell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 23:10:51 by gifanell          #+#    #+#             */
/*   Updated: 2025/08/25 13:19:49 by gifanell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutex_array(pthread_mutex_t *forks, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
		{
			cleanup_mutex_array(forks, i);
			return (1);
		}
		i++;
	}
	return (0);
}

void	cleanup_mutex_array(pthread_mutex_t *forks, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
}

int	init_forks(t_table	*table)
{
	int	error;

	table->forks = malloc(sizeof(pthread_mutex_t) * table->philo_nbr);
	if (!table->forks)
		return (1);
	error = init_mutex_array(table->forks, table->philo_nbr);
	if (error)
		return (free(table->forks), 1);
	if (pthread_mutex_init(&table->print_lock, NULL) != 0)
	{
		cleanup_mutex_array(table->forks, table->philo_nbr);
		free(table->forks);
		return (1);
	}
	if (pthread_mutex_init(&table->death_lock, NULL) != 0)
	{
		pthread_mutex_destroy(&table->print_lock);
		cleanup_mutex_array(table->forks, table->philo_nbr);
		free(table->forks);
		return (1);
	}
	return (0);
}

void	destroy_forks(t_table *table, t_philo *philos)
{
	int	i;

	if (!table || !table->forks)
		return ;
	i = 0;
	while (i < table->philo_nbr)
	{
		pthread_mutex_destroy(&table->forks[i]);
		pthread_mutex_destroy(&philos[i].meal_lock);
		i++;
	}
	pthread_mutex_destroy(&table->print_lock);
	pthread_mutex_destroy(&table->death_lock);
	free(table->forks);
	table->forks = NULL;
}
/*
Non e' una buona idea dare a tutti i filosofi la stessa logica per le forks,
perche si puo' creare un deadlock
(tutti prendono una fork (la sx o dx, dipende da come e' scritto nel codice) e aspettano la seconda)

Esempio:
philos = 2
forks:
- fork 0
- fork 1

philo_hands:
- philo 0
	- left: fork 0
	- right: fork 1
- philo 1
	- left: fork 1
	- right: fork 0

Soluzione:
invertire la sinistra e destra di uno dei filosofi
philo_hands:
- philo 0
	- left: fork 0
	- right: fork 1
- philo 1
	- left: fork 0
	- right: fork 1

In questo modo entrambi "combattono" per ottenere la prima fork,
e chi vince si prende con "calma" la seconda,
perche' l'altro filosofo aspetta ancora di prendere la prima fork

*/
int	init_philo(t_philo *philos, t_table *table)
{
	int	i;
	int	n;

	i = 0;
	n = table->philo_nbr;
	while (i < n)
	{
		philos[i].id = i;
		philos[i].meals_counter = 0;
		philos[i].last_meal_time = table->start_simulation;
		philos[i].left_fork = &table->forks[i];
		philos[i].right_fork = &table->forks[(i + 1) % n];
		if (i == n - 1)
		{
			philos[i].left_fork = philos[i].right_fork;
			philos[i].right_fork = &table->forks[i];
		}
		philos[i].table = table;
		pthread_mutex_init(&philos[i].meal_lock, NULL);
		i++;
	}
	return (0);
}
