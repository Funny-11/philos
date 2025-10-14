/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gifanell <gifanell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 15:43:58 by gifanell          #+#    #+#             */
/*   Updated: 2025/10/14 15:44:03 by gifanell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	pthread_get_long(pthread_mutex_t *lock, long *value)
{
	long	res;

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
