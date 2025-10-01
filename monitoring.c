/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gifanell <gifanell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 14:57:41 by gifanell          #+#    #+#             */
/*   Updated: 2025/09/22 15:12:21 by gifanell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	all_philos_full(t_philo *philos)
{
	int		i;
	int		full;
	int		meals_counter;
	t_table	*table;

	table = philos[0].table;
	i = 0;
	full = 0;
	while (i < table->philo_nbr)
	{
		meals_counter = pthread_get_long(&philos[i].meal_lock,
				&philos[i].meals_counter);
		if (table->nbr_limitsmeals != -1
			&& meals_counter >= table->nbr_limitsmeals)
			full++;
		i++;
	}
	return (table->nbr_limitsmeals != -1 && full == table->philo_nbr);
}

int	check_philo_death(t_table *table, t_philo *philos, int i,
	long current_time)
{
	long	last_meal_time;

	pthread_mutex_lock(&philos[i].meal_lock);
	last_meal_time = current_time - philos[i].last_meal_time;
	pthread_mutex_unlock(&philos[i].meal_lock);
	if (last_meal_time >= table->time_to_die)
	{
		pthread_mutex_lock(&table->print_lock);
		if (!table->end_simulation)
		{
			printf("%ld %d died\n",
				current_time - table->start_simulation,
				philos[i].id + 1);
			pthread_mutex_lock(&table->death_lock);
			table->end_simulation = 1;
			pthread_mutex_unlock(&table->death_lock);
		}
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
	long	current_time;

	philos = (t_philo *)arg;
	table = philos[0].table;
	while (!pthread_get_bool(&table->death_lock, &table->end_simulation))
	{
		i = 0;
		while (i < table->philo_nbr
			&& !pthread_get_bool(&table->death_lock, &table->end_simulation))
		{
			current_time = get_timestamp();
			if (check_philo_death(table, philos, i, current_time))
				return (NULL);
			i++;
			if (all_philos_full(philos))
			{
				table->end_simulation = 1;
				return (NULL);
			}
			// questo usleep serve per fare in modo che il computer possa gestire le risorse in modo efficiente (divide il consumo tra tutti i processori virtuali)
			// per capire meglio cosa succede, lancia htop, monitora l'uso della cpu (%) con e senza `usleep`
			usleep(1);
		}
	}
	return (NULL);
}
