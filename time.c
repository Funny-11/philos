/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gifanell <gifanell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 17:41:52 by gifanell          #+#    #+#             */
/*   Updated: 2025/08/25 13:19:18 by gifanell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_timestamp(void)
{
	struct timeval	tv;
	long			timestamp;

	gettimeofday(&tv, NULL);
	timestamp = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (timestamp);
}

/*
Non e' necessario fare il check nel loop, se rallenta troppo il programma
si puo' considerare di toglierlo e fare solo il check del >= duration
*/
void	smart_sleep(long duration, t_table *table)
{
	long	start_time;

	start_time = get_timestamp();
	while (!pthread_get_bool(&table->death_lock, &table->end_simulation))
	{
		if ((get_timestamp() - start_time) >= duration)
			break ;
		usleep(500);
	}
}

void	print_action(t_philo *philo, const char *action)
{
	t_table	*table;
	long	timestamp;

	table = philo->table;
	pthread_mutex_lock(&table->print_lock);
	if (!pthread_get_bool(&table->death_lock, &table->end_simulation))
	{
		timestamp = get_timestamp() - table->start_simulation;
		printf("%ld %d %s\n", timestamp, philo->id + 1, action);
	}
	pthread_mutex_unlock(&table->print_lock);
}
