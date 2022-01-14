/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanja <ttanja@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 22:00:50 by ttanja            #+#    #+#             */
/*   Updated: 2021/12/08 22:24:49 by ttanja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	if_error(t_philosopher *philosopher)
{
	sem_wait(philosopher->sem_print);
	sem_post(philosopher->sem_stop);
	printf("%s\n", "error create children thread");
	exit(1);
}

void	start_child(t_philosopher *philosopher)
{
	pthread_t	thread;
	int			error;
	int			i;

	i = 0;
	while (philosopher->id == philosopher->count && ++i <= philosopher->count)
	{
		sem_post(philosopher->sem_create);
		usleep(1);
	}
	sem_wait(philosopher->sem_create);
	philosopher->time_start = get_time();
	philosopher->time_start_last_eat = get_time();
	error = pthread_create(&thread, NULL, self_check, philosopher);
	if (error)
		if_error(philosopher);
	while (!philosopher->flag_stop)
		live_cycle(philosopher);
	pthread_join(thread, NULL);
	pthread_detach(thread);
	destroy_all(philosopher, philosopher->count);
	exit(1);
}

void	live_cycle(t_philosopher *philosopher)
{
	sem_wait(philosopher->sem_forks);
	sem_wait(philosopher->sem_print);
	printf("%u %d has taken a forks\n", (unsigned int)get_time()
		- philosopher->time_start, philosopher->id);
		philosopher->time_start_last_eat = get_time();
	printf("%u %d is eating\n", philosopher->time_start_last_eat
		- philosopher->time_start, philosopher->id);
	sem_post(philosopher->sem_print);
	ft_usleep(philosopher->time_to_eat);
	sem_post(philosopher->sem_forks);
	philosopher->ate_count++;
	philosopher->time_start_last_sleap = get_time();
	sem_wait(philosopher->sem_print);
	printf("%u %d is sleeping\n", philosopher->time_start_last_sleap
		- philosopher->time_start, philosopher->id);
	sem_post(philosopher->sem_print);
	ft_usleep(philosopher->time_to_sleep);
	philosopher->time_start_last_thinking = get_time();
	sem_wait(philosopher->sem_print);
	printf("%u %d is thinking\n", philosopher->time_start_last_thinking
		- philosopher->time_start, philosopher->id);
	sem_post(philosopher->sem_print);
}

void	*self_check(void *philosopher)
{
	t_philosopher	*temp;

	temp = (t_philosopher *)philosopher;
	while (42)
	{
		if (temp->time_to_die < (int)(get_time() - temp->time_start_last_eat))
		{
			sem_wait(temp->sem_print);
			printf("%u %d is dead\n", (unsigned int)get_time()
				- temp->time_start, temp->id);
			sem_post(temp->sem_stop);
		}
		else if (temp->ate_norm > -1 && temp->ate_count == temp->ate_norm)
		{
			temp->flag_stop++;
			break ;
		}
		usleep(5);
	}
	return (0);
}
