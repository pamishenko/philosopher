/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanja <ttanja@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 20:25:40 by ttanja            #+#    #+#             */
/*   Updated: 2021/12/05 19:44:12 by ttanja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include "philosopher.h"

long int	get_time(void)
{
	struct timeval	time;
	long int		res;

	gettimeofday(&time, NULL);
	res = (time.tv_sec * (long)1000) + (time.tv_usec / 1000);
	return (res);
}

void	ft_usleep(int ms)
{
	long	start;

	start = get_time();
	usleep(ms * 920);
	while (get_time() < start + ms)
		usleep(ms * 3);
}

void	set_time_create(t_philosopher *philoslpher)
{
	int		i;
	long	start_time;

	i = -1;
	start_time = get_time();
	philoslpher->spec->start_time = start_time;
	while (++i <= philoslpher->spec->count - 1)
		philoslpher[i].time_start_last_eat = start_time;
}
