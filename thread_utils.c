/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gifanell <gifanell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 15:43:58 by gifanell          #+#    #+#             */
/*   Updated: 2025/10/20 20:16:16 by gifanell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// TODO: rimuovere
long	pthread_get_long(pthread_mutex_t *lock, long *value)
{
	long	res;

	pthread_mutex_lock(lock);
	res = *value;
	pthread_mutex_unlock(lock);
	return (res);
}

size_t	pthread_get_sizet(pthread_mutex_t *lock, size_t *value)
{
	size_t	res;

	pthread_mutex_lock(lock);
	res = *value;
	pthread_mutex_unlock(lock);
	return (res);
}

bool	pthread_get_bool(pthread_mutex_t *lock, bool *value)
{
	bool	res;

	pthread_mutex_lock(lock);
	res = *value;
	pthread_mutex_unlock(lock);
	return (res);
}
