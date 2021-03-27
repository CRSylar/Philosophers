/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cromalde <cromalde@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 19:50:30 by cromalde          #+#    #+#             */
/*   Updated: 2021/03/27 21:23:56 by cromalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <errno.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <string.h>
# include <pthread.h>
# include <semaphore.h>
# include <sys/wait.h>
# include <fcntl.h>


typedef struct      s_all
{
	int					philo;
	int					sleep;
	int					eat;
	int					die;
	pthread_mutex_t		*prev;
	pthread_mutex_t		forks;
}                   t_all;

int		ft_atoi(const char *nptr);

#endif