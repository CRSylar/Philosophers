/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cromalde <cromalde@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 11:30:18 by cromalde          #+#    #+#             */
/*   Updated: 2021/04/05 16:43:34 by cromalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_THREE_H
# define PHILO_THREE_H

# include <stdlib.h>
# include <errno.h>
# include <unistd.h>
# include <stdio.h>
# include <semaphore.h>
# include <fcntl.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <signal.h>

struct	s_all;

typedef struct s_philo
{
	pid_t				*pid;
	int					id;
	int					m_start;
	int					m_end;
	unsigned long		t_last_meal;
	unsigned long		t_to_live;
	pthread_t			t;
	sem_t				*eating;
	struct s_all		*all;
}				t_philo;

typedef struct s_all
{
	t_philo				p;
	int					status;
	int					philo;
	int					sleep;
	int					eat;
	int					die;
	int					is_dead;
	int					n_meal;
	int					total_meal;
	unsigned long		time_start;
	sem_t				*forks;
	sem_t				*print;
	sem_t				*dead;
}					t_all;

int				ft_atoi(const char *nptr);
unsigned long	now(void);
void			*life_status(void *ptr);
void			ft_print(t_philo *p, char *str);
void			go_to_sleep(int time, t_all *all);

#endif
