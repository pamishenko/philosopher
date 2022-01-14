/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanja <ttanja@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 01:15:54 by ttanja            #+#    #+#             */
/*   Updated: 2021/12/08 22:41:39 by ttanja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "philosopher.h"

t_philosopher	*set_specification(int argc, char **argv,
	t_philosopher	*philosopher)
{
	philosopher = ft_calloc(sizeof(t_philosopher), 1);
	if (!philosopher)
		return (NULL);
	philosopher->count = ft_atoi(argv[1]);
	philosopher->time_to_die = ft_atoi(argv[2]);
	philosopher->time_to_eat = ft_atoi(argv[3]);
	philosopher->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		philosopher->ate_norm = ft_atoi(argv[5]);
	else
		philosopher->ate_norm = -1;
	philosopher->time_start = get_time();
	return (philosopher);
}

t_philosopher	*parse_specification(int argc, char **argv,
	t_philosopher	*philosopher)
{
	int	i;
	int	temp;

	i = 0;
	temp = argc;
	if (temp < 5 || temp > 6)
		return (NULL);
	while (--temp > 0)
	{
		while (argv[temp][i])
		{
			if (!ft_isdigit(argv[temp][i]))
				return (NULL);
			i++;
		}
	}
	if (ft_atoi(argv[1]) > 300)
		return (NULL);
	return (set_specification(argc, argv, philosopher));
}
