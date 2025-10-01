
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