/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanja <ttanja@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 22:14:00 by ttanja            #+#    #+#             */
/*   Updated: 2021/12/05 19:58:01 by ttanja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "philosopher.h"

int	sleaping(t_philosopher *philosopher)
{
	if (philosopher->spec->num_dead != 0)
		return (1);
	philosopher->time_start_last_sleap = get_time();
	printf("%ld %d is sleeping\n", philosopher->time_start_last_sleap
		- philosopher->spec->start_time, philosopher->id);
	ft_usleep(philosopher->spec->time_to_sleep);
	philosopher->time_start_last_thinking = get_time();
	printf("%ld %d is thinking\n", philosopher->time_start_last_thinking
		- philosopher->spec->start_time, philosopher->id);
	return (0);
}

int	eating(t_philosopher *philosopher)
{
	if (philosopher->spec->num_dead != 0)
		return (1);
	if ((philosopher->id % 2) == 0)
		ft_usleep(1);
	pthread_mutex_lock(philosopher->l_fork);
	printf("%ld %d has taken a fork(r)\n", get_time()
		- philosopher->spec->start_time, philosopher->id);
	pthread_mutex_lock(&philosopher->r_fork);
	printf("%ld %d has taken a fork(l)\n", get_time()
		- philosopher->spec->start_time, philosopher->id);
	philosopher->time_start_last_eat = get_time();
	printf("%ld %d is eating\n", philosopher->time_start_last_eat
		- philosopher->spec->start_time, philosopher->id);
	philosopher->ate_count++;
	ft_usleep(philosopher->spec->time_to_eat);
	pthread_mutex_unlock(philosopher->l_fork);
	pthread_mutex_unlock(&philosopher->r_fork);
	return (0);
}

int	get_min_ate(t_philosopher *philosopher)
{
	int				i;
	unsigned int	min;

	i = -1;
	min = philosopher[0].ate_count;
	while (++i < philosopher->spec->count)
	{
		if (min < philosopher->ate_count)
			min = philosopher->ate_count;
	}
	return (min);
}

void	*control(void *philosopher)
{
	int				i;
	long			min_ate;
	t_philosopher	*temp;

	temp = NULL;
	i = 0;
	temp = (t_philosopher *)philosopher;
	min_ate = 0;
	set_time_create(temp);
	while (((temp->spec->ate_count && temp->spec->ate_count > min_ate)
			|| temp->spec->ate_count == 0) && !temp->spec->num_dead)
	{
		min_ate = get_min_ate(temp);
		if (temp[i].spec->time_to_die
			<= get_time() - temp[i].time_start_last_eat)
		{
			temp[i].spec->num_dead = i + 1;
			break ;
		}
		if (++i == temp->spec->count)
			i = 0;
	}
	if (temp[i].spec->ate_count <= min_ate)
		temp[i].spec->time_end = get_time();
	return (NULL);
}

void	*live_cycle(void *philosopher)
{
	t_philosopher	*temp;

	temp = (t_philosopher *)philosopher;
	if (temp->spec->count == 1)
	{
		ft_usleep(temp->spec->time_to_die);
		return (NULL);
	}
	while (!temp->spec->num_dead)
	{
		eating(temp);
		sleaping(temp);
	}
	return (NULL);
}
