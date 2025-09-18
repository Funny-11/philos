/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gifanell <gifanell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 23:10:42 by gifanell          #+#    #+#             */
/*   Updated: 2025/08/25 13:19:47 by gifanell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		print_action(philo, "has taken right fork");
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "has taken left fork");
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "has taken left fork");
		pthread_mutex_lock(philo->right_fork);
		print_action(philo, "has taken right fork");
	}
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(100);
	while (!(philo->table->end_simulation))
	{
		philo_eat(philo);
		if (philo->table->nbr_limitsmeals != -1
			&& philo->meals_counter >= philo->table->nbr_limitsmeals)
			break ;
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}
