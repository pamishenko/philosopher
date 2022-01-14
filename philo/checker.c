/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanja <ttanja@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 01:15:54 by ttanja            #+#    #+#             */
/*   Updated: 2021/12/05 19:47:53 by ttanja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "philosopher.h"

t_specification	*set_specification(int argc, char **argv,
	t_specification	*specification)
{
	specification = ft_calloc(sizeof(t_specification), 1);
	if (!specification)
		return (NULL);
	specification->count = ft_atoi(argv[1]);
	specification->time_to_die = ft_atoi(argv[2]);
	specification->time_to_eat = ft_atoi(argv[3]);
	specification->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		specification->ate_count = ft_atoi(argv[5]);
	return (specification);
}

t_specification	*parse_specification(int argc, char **argv,
	t_specification	*specification)
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
	return (set_specification(argc, argv, specification));
}

void	destroy_specification(t_specification *specification)
{
	free(specification);
}
