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
	pthread_mutex_lock(philo->left_fork);
	print_action(philo, "has taken left fork");
	pthread_mutex_lock(philo->right_fork);
	print_action(philo, "has taken right fork");
}

/*
Invertito l'ordine dei unlock perche bisogna seguire l'ordine di acquisizione,
come uno stack.

Esempio:
Lock:
left
	|-> right

Unlock:
		right
left <--|
*/
void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	// non si fa niente, ci pensa il monitor ad avvisare che il philo e' morto.
	if (philo->table->philo_nbr == 1)
		return (NULL);
	// usleep minimo per creare un offset per i filosofi pari,
	// farli partire leggermente piu' tardi
	// per "bilanciare" l'uso delle forchette da tutti i filosofi
	if (philo->id % 2 == 0)
		usleep(50);
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
