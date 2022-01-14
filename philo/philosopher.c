/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanja <ttanja@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 01:30:14 by ttanja            #+#    #+#             */
/*   Updated: 2021/12/05 19:47:06 by ttanja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "philosopher.h"

t_philosopher	*create_philosophers(t_specification *spec)
{
	t_philosopher	*philosophers;
	int				i;

	i = -1;
	philosophers = ft_calloc(sizeof(t_philosopher), spec->count);
	if (!philosophers)
		return (NULL);
	while (++i < spec->count)
	{
		philosophers[i].id = i + 1;
		philosophers[i].spec = spec;
		pthread_mutex_init(&philosophers[i].r_fork, NULL);
		if (i - 1 >= 0)
			philosophers[i - 1].l_fork = &philosophers[i].r_fork;
	}
	philosophers[spec->count - 1].spec = spec;
	philosophers[spec->count - 1].id = spec->count;
	pthread_mutex_init(&philosophers[i].r_fork, NULL);
	if (spec->count > 1)
		philosophers[spec->count - 1].l_fork = &philosophers[0].r_fork;
	return (philosophers);
}

void	destroy_philosopher(t_philosopher *philosophers)
{
	int	count;

	count = philosophers->spec->count;
	while (--count >= 0)
	{
		pthread_mutex_destroy(&philosophers[count].r_fork);
		free(&philosophers[count]);
	}
}
