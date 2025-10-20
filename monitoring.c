/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gifanell <gifanell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 14:57:41 by gifanell          #+#    #+#             */
/*   Updated: 2025/10/20 20:23:11 by gifanell         ###   ########.fr       */
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
	if (table->nbr_limitsmeals == -1)
		return (0);
	while (i < table->philo_nbr)
	{
		if (table->nbr_limitsmeals != -1
			&& pthread_get_long(&philos[i].meal_lock,
			&philos[i].meals_counter) >= table->nbr_limitsmeals)
			full++;
		i++;
	}
	return (full == table->philo_nbr);
}

static void	end_simulation_on(t_table *table)
{
	pthread_mutex_lock(&table->dead_lock);
	table->end_simulation = 1;
	pthread_mutex_unlock(&table->dead_lock);
	return ;
}

int	check_philo_death(t_table *table, t_philo *philos, int i,
	size_t current_time)
{
	size_t	last_meal_time;

	pthread_mutex_lock(&philos[i].meal_lock);
	last_meal_time = philos[i].last_meal_time;
	pthread_mutex_unlock(&philos[i].meal_lock);
	if (last_meal_time == 0)
		return (0);
	if (current_time - last_meal_time >= (size_t)table->time_to_die)
	{
		end_simulation_on(table);
		pthread_mutex_lock(&table->print_lock);
		printf("%ld %d died\n",
			current_time - table->start_simulation,
			philos[i].id + 1);
		pthread_mutex_unlock(&table->print_lock);
		return (1);
	}
	return (0);
}


void	*monitor_routine(void *arg)
{
	t_philo	*philos;
	t_table	*table;
	int		i;
	size_t	current_time;
	int		satisfied_philos;

	philos = (t_philo *)arg;
	table = philos[0].table;
	while (1)
	{
		i = 0;
		satisfied_philos = 0;
		while (i < table->philo_nbr)
		{
			current_time = get_timestamp();
			if (check_philo_death(table, philos, i, current_time))
				return (NULL);
			i++;
		}
		if (all_philos_full(philos))
				return (end_simulation_on(table), NULL);
		usleep(50);
	}
	return (NULL);
}
