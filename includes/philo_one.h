/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cromalde <cromalde@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 19:50:30 by cromalde          #+#    #+#             */
/*   Updated: 2021/04/05 18:06:10 by cromalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <stdlib.h>
# include <errno.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <signal.h>

# define RED "\033[0;31m"
# define GRN "\033[0;32m"
# define YLL "\033[0;33m"
# define NC "\033[0m"

struct	s_all;

typedef struct s_philo
{
	int					id;
	int					lft_hand;
	int					rgt_hand;
	int					dop_start;
	int					dop_end;
	int					eat;
	unsigned long		t_last_meal;
	unsigned long		t_to_live;
	pthread_t			t;
	pthread_mutex_t		eating;
	struct s_all		*all;
}				t_philo;

typedef struct s_all
{
	t_philo				*p;
	int					philo;
	int					sleep;
	int					eat;
	int					die;
	int					is_dead;
	int					n_meal;
	int					total_meal;
	unsigned long		time_start;
	pthread_mutex_t		*forks;
	pthread_mutex_t		print;
	pthread_mutex_t		dead;
}					t_all;

int				ft_atoi(const char *nptr);
unsigned long	now(void);
void			*life_status(void *ptr);
void			ft_print(t_philo *p, char *str, char *color);
void			go_to_sleep(int time, t_all *all);

#endif
