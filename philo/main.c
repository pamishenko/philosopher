/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanja <ttanja@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 23:40:57 by ttanja            #+#    #+#             */
/*   Updated: 2021/12/05 20:03:44 by ttanja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "philosopher.h"

static char	create_all_thread(t_philosopher *philosopher,
	pthread_t	*threads, int *error)
{
	int	i;

	i = -1;
	while (++i < philosopher->spec->count)
	{
		*error = pthread_create(&threads[i], NULL, live_cycle, &philosopher[i]);
		if (*error != 0)
		{
			while (i-- != 0)
			{
				pthread_join(threads[i], NULL);
				pthread_detach(threads[i]);
			}
			pthread_join(threads[philosopher->spec->ate_count], NULL);
			pthread_detach(threads[philosopher->spec->ate_count]);
			return (-1);
		}
	}
	return (0);
}

static char	start_threads(t_philosopher *phil)
{
	pthread_t	*threads;
	int			error;

	threads = malloc(sizeof(pthread_t *) * phil->spec->count + 1);
	if (!threads)
		return (1);
	error = pthread_create(&threads[phil->spec->count], NULL, control, phil);
	if (error != 0)
	{
		free(threads);
		return (-1);
	}
	phil->spec->start_time = get_time();
	create_all_thread(phil, threads, &error);
	while (!phil->spec->time_end && !phil->spec->num_dead)
		ft_usleep(5);
	if (phil->spec->num_dead)
		printf("%ld %d is dead\n", get_time() - phil->spec->start_time,
			phil->spec->num_dead);
	else if (phil->spec->ate_count)
		printf("%ld Done, no dead philosopher\n",
			get_time() - phil->spec->start_time);
	free(threads);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_specification	*specification;
	t_philosopher	*philosophs;
	char			error;

	specification = NULL;
	specification = parse_specification(argc, argv, specification);
	if (!specification)
	{
		printf("error\n");
		return (-1);
	}
	philosophs = create_philosophers(specification);
	error = start_threads(philosophs);
	if (error)
	{
		free(philosophs);
		free(specification);
		return (1);
	}
	free(philosophs);
	free(specification);
	return (0);
}
