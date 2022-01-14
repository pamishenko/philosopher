/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanja <ttanja@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 07:22:57 by ttanja            #+#    #+#             */
/*   Updated: 2021/12/05 19:49:46 by ttanja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <pthread.h>
# include <limits.h>
# include <sys/time.h>

typedef struct s_specification
{
	int				count;
	long			start_time;
	int				time_to_die;
	int				time_to_sleep;
	int				time_to_eat;
	unsigned int	ate_count;
	int				num_dead;
	int				time_end;
}	t_specification;

typedef struct s_philosopher
{
	int						id;
	t_specification			*spec;
	pthread_mutex_t			r_fork;
	pthread_mutex_t			*l_fork;
	long int				time_start_last_eat;
	long int				time_start_last_sleap;
	long int				time_start_last_thinking;
	unsigned int			ate_count;
}	t_philosopher;

//pilosoph control
t_specification
*parse_specification(int argc, char **argv, t_specification	*specification);
void
destroy_specification(t_specification *specification);
t_philosopher
*create_philosophers(t_specification *specification);
void
destroy_philosopher(t_philosopher *philosophers);

//Threads control
void
*control(void *philosopher);
void
*live_cycle(void *philosopher);
int
eating(t_philosopher *philosopher);
int
sleaping_thinking(t_philosopher *philosopher);
int
thinking(t_philosopher *philosopher);

//utils
void
ft_usleep(int time);
long
get_time(void);
void
set_time_create(t_philosopher *philoslpher);

//libfunction
int
ft_atoi(const char *str);
void
ft_bzero(void *s, size_t n);
void
*ft_calloc(size_t count, size_t size);
int
ft_isdigit(int c);
void
*ft_memset(void *b, int c, size_t len);

#endif