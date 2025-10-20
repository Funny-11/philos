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

size_t	get_timestamp(void)
{
	struct timeval	tv;
	size_t			timestamp;

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
	size_t	start_time;
	(void)table;

	start_time = get_timestamp();
	while (!((get_timestamp() - start_time) >= (size_t)duration))
	{
		usleep(50);
	}
}

void	print_action(t_philo *philo, const char *action)
{
	t_table	*table;
	size_t	timestamp;

	table = philo->table;
	if (pthread_get_bool(&table->dead_lock, &table->end_simulation))
		return ;
	pthread_mutex_lock(&table->print_lock);
	timestamp = get_timestamp() - table->start_simulation;
	printf("%ld %d %s\n", timestamp, philo->id + 1, action);
	pthread_mutex_unlock(&table->print_lock);
}
