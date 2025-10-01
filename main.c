/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gifanell <gifanell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 23:10:25 by gifanell          #+#    #+#             */
/*   Updated: 2025/09/22 15:10:13 by gifanell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	alloc_init(int argc, char **argv, t_table *table, t_philo **philos)
{
	if (parse_arguments(argc, argv, table))
	{
		printf("Error: Invalid arguments\n");
		return (1);
	}
	if (init_forks(table))
	{
		printf("Error: Fork initialization failed\n");
		return (1);
	}
	*philos = malloc(sizeof(t_philo) * table->philo_nbr);
	if (!philos)
	{
		destroy_forks(table, *philos);
		printf("Error: Memory allocation failed\n");
		return (1);
	}
	init_philo(*philos, table);
	return (0);
}

int	create_threads(t_table *table, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < table->philo_nbr)
	{
		if (pthread_create(&philos[i].thread_id, NULL,
				&philo_routine, &philos[i]) != 0)
		{
			printf("Error: Thread creation failed\n");
			return (1);
		}
		i++;
	}
	return (0);
}

void	join_and_cleanup(t_table *table, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < table->philo_nbr)
		pthread_join(philos[i++].thread_id, NULL);
	destroy_forks(table, philos);
	free(philos);
}

int	main(int argc, char **argv)
{
	t_table		table;
	t_philo		*philos;

	table = (t_table){0}; // inizializzazione: tutto a zero
	if (alloc_init(argc, argv, &table, &philos))
		return (1);
	if (create_threads(&table, philos))
		return (1);
	// invece di creare un thread per monitorare, e aspettare che questo finisca
	// si puo' semplicemente usare il thread principale che non viene usato
	monitor_routine(philos);
	join_and_cleanup(&table, philos);
	return (0);
}
