/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gifanell <gifanell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 23:10:25 by gifanell          #+#    #+#             */
/*   Updated: 2025/09/18 20:35:24 by gifanell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdbool.h>
# include <sys/time.h>
# include <limits.h>

/*
#define EAT "is eating"
#define SLEEP "is sleeping"
#define THINK "is thinking"
#define DIE "is dead"
#define SURVIVE "has finished his theory"
#define LF_TAKE "has taken his left fork"
#define RF_TAKE "has taken his right fork"
#define LF_REL "released left fork"
#define RF_REL "released right fork"
*/

/******		STRUTTURE		******/
typedef struct s_table
{
	long			philo_nbr;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			nbr_limitsmeals;
	long			start_simulation;
	bool			end_simulation;

	pthread_mutex_t	print_lock;
	pthread_mutex_t	*forks;
}	t_table;

typedef struct s_philo
{
	int					id;
	long				meals_counter;
	long				last_meal_time;

	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		meal_lock;

	t_table				*table;
	pthread_t			thread_id;
}	t_philo;

/******		PROTOTIPI FUNZIONI		******/
void	cleanup_mutex_array(pthread_mutex_t *forks, int count);
void	destroy_forks(t_table *table);
void	smart_sleep(long duration, t_table *table);
void	print_action(t_philo *philo, const char *action);
void	*philo_routine(void	*arg);
void	*monitor_routine(void *arg);
void	philo_eat(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	philo_think(t_philo *philo);
void	take_forks(t_philo *philo);
void	drop_forks(t_philo *philo);
long	get_timestamp(void);
int		init_mutex_array(pthread_mutex_t *forks, int count);
int		init_forks(t_table *table);
int		init_philo(t_philo *philos, t_table *table);
int		parse_arguments(int argc, char **argv, t_table *table);

#endif
