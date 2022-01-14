/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanja <ttanja@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 07:22:57 by ttanja            #+#    #+#             */
/*   Updated: 2021/12/08 22:36:37 by ttanja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <semaphore.h>
# include <pthread.h>
# include <sys/time.h>
# include <fcntl.h>
# include <sys/stat.h>
# include "philosopher.h"

typedef struct s_philosopher
{
	int				id;
	unsigned int	time_start;
	int				count;
	unsigned int	time_start_last_eat;
	unsigned int	time_start_last_sleap;
	unsigned int	time_start_last_thinking;
	long			ate_norm;
	long			ate_count;
	int				time_to_die;
	int				time_to_sleep;
	int				time_to_eat;
	int				flag_stop;
	pid_t			*ph_proc;
	sem_t			*sem_create;
	sem_t			*sem_print;
	sem_t			*sem_forks;
	sem_t			*sem_stop;
}	t_philosopher;

//pilosoph control
void			start_child(t_philosopher *philosopher);
int				destroy_all(t_philosopher *philosopher, int proc_count);

//children_procceses
void			start_child(t_philosopher *philosopher);
void			live_cycle(t_philosopher *philosopher);
void			*self_check(void *philosopher);

//utils
t_philosopher	*parse_specification(int argc, char **argv,
					t_philosopher *philosopher);
void			ft_usleep(int time);
long			get_time(void);
int				destroy_all(t_philosopher *philosopher, int proc_count);
void			ft_sem_ulink(void);

//libfunction
int				ft_atoi(const char *str);
void			ft_bzero(void *s, size_t n);
void			*ft_calloc(size_t count, size_t size);
int				ft_isdigit(int c);
void			*ft_memset(void *b, int c, size_t len);

#endif