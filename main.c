/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gifanell <gifanell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 23:10:25 by gifanell          #+#    #+#             */
/*   Updated: 2025/09/18 20:52:13 by gifanell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_table		table;
	t_philo		*philos;
	pthread_t	monitor_thread;
	int			i;

	if (parse_arguments(argc, argv, &table))
		return (printf("Error: Invalid arguments\n"));
	if (init_forks(&table))
		return (printf("Error: Fork initialization failed\n"), 1);
	philos = malloc(sizeof(t_philo) * table.philo_nbr);
	if (!philos)
	{
		destroy_forks(&table);
		printf("Error: Memory allocation failed\n");
		return (1);
	}
	init_philo(philos, &table);
	i = 0;
	while (i < table.philo_nbr)
	{
		if (pthread_create(&philos[i].thread_id, NULL, &philo_routine,
				&philos[i]) != 0)
			return (printf("Error: Thread creation failed\n"));
		i++;
	}
	if (pthread_create(&monitor_thread, NULL, &monitor_routine, philos) != 0)
		return (printf("Error: Monitor thread creation failed\n"));
	i = 0;
	while (i < table.philo_nbr)
		pthread_join(philos[i++].thread_id, NULL);
	pthread_join(monitor_thread, NULL);
	destroy_forks(&table);
	free(philos);
	return (0);
}
