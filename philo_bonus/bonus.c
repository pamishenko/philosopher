/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanja <ttanja@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 15:27:02 by ttanja            #+#    #+#             */
/*   Updated: 2021/12/08 22:45:51 by ttanja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	wait_chaild(t_philosopher *philosopher)
{
	int	i;

	i = -1;
	while (++i < philosopher->count)
		waitpid(-1, NULL, 0);
	sem_post(philosopher->sem_stop);
}

static void	*master_thread(void *philosopher)
{
	t_philosopher	*temp;

	temp = (t_philosopher *)philosopher;
	sem_wait(temp->sem_stop);
	while (--temp->count >= 0)
		kill(temp->ph_proc[temp->count], SIGKILL);
	return (NULL);
}

static void	create_child_processes(t_philosopher *philosopher, int i)
{
	pthread_t	theread_id;
	int			error;

	while (++i < philosopher->count)
	{
		philosopher->ph_proc[i] = fork();
		if (philosopher->ph_proc[i] == -1)
		{
			destroy_all(philosopher, i + 1);
			return ;
		}
		if (philosopher->ph_proc[i] == 0)
		{
			philosopher->id = i + 1;
			start_child(philosopher);
			break ;
		}
	}
	error = pthread_create(&theread_id, NULL, master_thread, philosopher);
	if (error)
		destroy_all(philosopher, philosopher->count);
	wait_chaild(philosopher);
	pthread_join(theread_id, NULL);
	pthread_detach(theread_id);
}

int	main(int argc, char *argv[])
{
	t_philosopher	*philo;

	ft_sem_ulink();
	philo = NULL;
	philo = parse_specification(argc, argv, philo);
	if (!philo)
		return (1);
	philo->ph_proc = (pid_t *)ft_calloc(sizeof(pid_t), philo->count);
	if (!philo->ph_proc)
	{
		destroy_all(philo, 0);
		return (1);
	}
	philo->sem_create = sem_open("create", O_CREAT, S_IRWXU, 0);
	philo->sem_print = sem_open("print", O_CREAT, S_IRWXU, 1);
	philo->sem_forks = sem_open("forks", O_CREAT, S_IRWXU, (philo->count / 2));
	philo->sem_stop = sem_open("stop", O_CREAT, S_IRWXU, 0);
	create_child_processes(philo, -1);
	destroy_all(philo, philo->count);
	return (0);
}
