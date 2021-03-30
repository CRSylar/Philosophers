/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cromalde <cromalde@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 19:50:30 by cromalde          #+#    #+#             */
/*   Updated: 2021/03/30 17:12:51 by cromalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <pthread.h>
# include <semaphore.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <signal.h>

typedef struct			s_all
{
	int					philo;
	int					sleep;
	int					eat;
	int					die;
	int					n_meal;
	int					action;
	long				start;
	long				last_meal;
	pthread_mutex_t		*status;
	pthread_mutex_t		*meals;
	pthread_mutex_t		*prev;
	pthread_mutex_t		forks;
}						t_all;

int		ft_atoi(const char *nptr);

#endif
