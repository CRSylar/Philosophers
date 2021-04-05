/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cromalde <cromalde@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 21:20:10 by cromalde          #+#    #+#             */
/*   Updated: 2021/04/05 18:09:11 by cromalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_one.h"

void	go_to_sleep(int time, t_all *all)
{
	unsigned long	end;

	end = now() + time;
	while (now() < end && !all->is_dead)
		usleep(time);
}

void	*life_status(void *ptr)
{
	t_philo	*p;

	p = (t_philo *)ptr;
	while (!p->all->is_dead)
	{
		usleep(100);
		pthread_mutex_lock(&p->eating);
		if (now() - p->t_last_meal > (unsigned long)p->all->die && \
			 !p->all->is_dead)
		{
			p->all->is_dead = 1;
			pthread_mutex_unlock(&p->eating);
			pthread_mutex_lock(&p->all->dead);
			printf(RED" %lu %d is died\n"NC, (now() - p->all->time_start), p->id);
			return (0);
		}
		else if (!p->all->is_dead && p->dop_end != -1 && \
			 p->dop_start >= p->dop_end)
			return (0);
		pthread_mutex_unlock(&p->eating);
	}
	return (0);
}

void	ft_print(t_philo *p, char *str, char *color)
{
	if (!p->all->is_dead && p->all->total_meal != 0)
	{
		pthread_mutex_lock(&p->all->print);
		if (!p->all->is_dead && p->all->total_meal != 0)
			printf("%s %lu %d %s\n"NC, color, (now() - p->all->time_start), p->id, str);
		pthread_mutex_unlock(&p->all->print);
	}
}

unsigned long	now(void)
{
	struct timeval	t;

	gettimeofday(&t, 0);
	return ((t.tv_sec * (unsigned long)1000) + (t.tv_usec / 1000));
}

int	ft_atoi(const char *nptr)
{
	unsigned int		out;
	int					neg;

	out = 0;
	neg = 1;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == 32)
		nptr++;
	if ((*nptr == '-') || (*nptr == '+'))
	{
		if (*nptr == '-')
			neg = -1;
		nptr++;
	}
	if (*nptr < '0' || *nptr > '9')
		return ((errno = 1));
	while (*nptr >= '0' && *nptr <= '9' && out < 2147483647)
		out = (out * 10) + (*nptr++ - '0');
	if ((out == 2147483648 && neg == -1) || (out < 2147483648))
		return (out * neg);
	if (neg == 1 && out != 0)
		return ((errno = 1));
	return ((errno = 1));
}
