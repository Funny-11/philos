/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gifanell <gifanell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 23:11:02 by gifanell          #+#    #+#             */
/*   Updated: 2025/10/14 15:52:54 by gifanell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_atoi(const char *str)
{
	long	n;

	n = 0;
	while (*str >= '0' && *str <= '9')
		n = n * 10 + (*str++ - '0');
	return ((int)n);
}

int	parse_arguments(int argc, char **argv, t_table *table)
{
	if (argc != 5 && argc != 6)
		return (1);
	table->philo_nbr = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		table->nbr_limitsmeals = ft_atoi(argv[5]);
	else
		table->nbr_limitsmeals = -1;
	if (table->philo_nbr <= 0
		|| table->time_to_die <= 0
		|| table->time_to_die <= 0
		|| table->time_to_eat <= 0
		|| table->time_to_eat <= 0
		|| table->time_to_sleep <= 0
		|| table->time_to_sleep <= 0
		|| (argc == 6 && table->nbr_limitsmeals <= 0))
		return (1);
	table->end_simulation = 0;
	table->start_simulation = get_timestamp();
	return (0);
}
