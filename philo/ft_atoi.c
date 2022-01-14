/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanja <ttanja@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 16:25:53 by ttanja            #+#    #+#             */
/*   Updated: 2021/11/28 01:09:41 by ttanja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	ft_atoi(const char *str)
{
	char				pozitive;
	long long int		result;

	pozitive = 1;
	result = 0;
	while ((*str >= '\t' && *str <= '\r') || *str == ' ')
		str++;
	if (*str == '-')
		pozitive *= -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
	{
		if (*str <= '9' && *str >= '0')
			result = (result * 10) + *str - 48;
		else
			break ;
		str++;
	}
	return (result * pozitive);
}
