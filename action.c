/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gifanell <gifanell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 20:40:53 by gifanell          #+#    #+#             */
/*   Updated: 2025/09/22 14:49:47 by gifanell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat(t_philo *philo)
{
	take_forks(philo);
	pthread_mutex_lock(&philo->table->print_lock);
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal_time = get_timestamp();
	pthread_mutex_unlock(&philo->table->print_lock);
	print_action(philo, "is eating");
	smart_sleep(philo->table->time_to_eat, philo->table);
	philo->meals_counter++;
	pthread_mutex_unlock(&philo->meal_lock);
	drop_forks(philo);
}

void	philo_sleep(t_philo *philo)
{
	print_action(philo, "is sleeping");
	smart_sleep(philo->table->time_to_sleep, philo->table);
}

void	philo_think(t_philo *philo)
{
	print_action(philo, "is thinking");
}
