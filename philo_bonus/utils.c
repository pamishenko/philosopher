/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanja <ttanja@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 20:25:40 by ttanja            #+#    #+#             */
/*   Updated: 2021/12/08 22:41:18 by ttanja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <sys/wait.h>
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
	usleep(ms * 900);
	while (get_time() < start + ms)
		usleep(ms * 3);
}

int	destroy_all(t_philosopher *philosopher, int proc_count)
{
	if (!philosopher)
		return (1);
	while (proc_count-- > 0)
		kill(philosopher->ph_proc[proc_count - 1], SIGKILL);
	sem_close(philosopher->sem_create);
	sem_close(philosopher->sem_forks);
	sem_close(philosopher->sem_print);
	sem_close(philosopher->sem_stop);
	sem_unlink("create");
	sem_unlink("forks");
	sem_unlink("print");
	sem_unlink("stop");
	if (!philosopher->ph_proc)
		free(philosopher->ph_proc);
	free (philosopher);
	return (0);
}

void	ft_sem_ulink(void)
{
	sem_unlink("create");
	sem_unlink("forks");
	sem_unlink("print");
	sem_unlink("stop");
}
