/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gifanell <gifanell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 14:57:41 by gifanell          #+#    #+#             */
/*   Updated: 2025/09/18 20:40:05 by gifanell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	all_philos_full(t_philo *philos)
{
	int		i;
	int		full;
	t_table	*table;

	table = philos[0].table;
	i = 0;
	full = 0;
	while (i < table->philo_nbr)
	{
		if (table->nbr_limitsmeals != -1
			&& philos[i].meals_counter >= table->nbr_limitsmeals)
			full++;
		i++;
	}
	return (table->nbr_limitsmeals != -1 && full == table->philo_nbr);
}

void	*monitor_routine(void *arg)
{
	t_philo	*philos;
	t_table	*table;
	int		i;
	long	current_time;
	long	last_meal_time;

	philos = (t_philo *)arg;
	table = philos[0].table;
	while (!table->end_simulation)
	{
		i = 0;
		while (i < table->philo_nbr && !table->end_simulation)
		{
			current_time = get_timestamp();
			last_meal_time = current_time - philos[i].last_meal_time;
			if (last_meal_time >= table->time_to_die)
			{
				if (!table->end_simulation)
				{
					pthread_mutex_lock(&table->print_lock);
					printf("%ld %d died\n",
						current_time - table->start_simulation,
						philos[i].id + 1);
					table->end_simulation = 1;
					pthread_mutex_unlock(&table->print_lock);
					return (NULL);
				}
			}
			i++;
			if (all_philos_full(philos))
			{
				table->end_simulation = 1;
				return (NULL);
			}
			usleep(1000);
		}
	}
	return (NULL);
}
