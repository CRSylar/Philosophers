/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_one.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cromalde <cromalde@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 19:49:28 by cromalde          #+#    #+#             */
/*   Updated: 2021/04/05 18:05:45 by cromalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_one.h"

int	ft_check_imput(int ac, char **av, t_all *all)
{
	if (ac < 5 || ac > 6)
		return (printf("Wrong number of arguments\n"));
	all->philo = ft_atoi(av[1]);
	all->die = ft_atoi(av[2]);
	all->eat = ft_atoi(av[3]);
	all->sleep = ft_atoi(av[4]);
	if (ac == 6)
		all->n_meal = ft_atoi(av[5]);
	else
		all->n_meal = -1;
	if ((all->philo < 1) || (all->die < 0) || (all->eat < 0) || \
		(all->sleep < 0) || (ac == 6 && all->n_meal < 0))
		return (printf("One or More Params is Wrong\n"));
	all->p = malloc(sizeof(t_philo) * all->philo);
	all->forks = malloc(sizeof(pthread_mutex_t) * all->philo);
	if (!all->p || !all->forks)
		return (printf("Error: memory not allocated\n"));
	pthread_mutex_init(&all->print, 0);
	pthread_mutex_init(&all->dead, 0);
	return (0);
}

void	go_eat(t_philo *p)
{
	pthread_mutex_lock(&p->all->forks[p->rgt_hand]);
	ft_print(p, "has taken a fork", YLL);
	pthread_mutex_lock(&p->all->forks[p->lft_hand]);
	ft_print(p, "has taken a fork", YLL);
	pthread_mutex_lock(&p->eating);
	p->t_last_meal = now();
	ft_print(p, "is eating", GRN);
	p->dop_start++;
	if (p->all->total_meal > 0)
		p->all->total_meal -= 1;
	go_to_sleep(p->all->eat, p->all);
	pthread_mutex_unlock(&p->eating);
	pthread_mutex_unlock(&p->all->forks[p->rgt_hand]);
	pthread_mutex_unlock(&p->all->forks[p->lft_hand]);
	ft_print(p, "is sleeping", YLL);
	go_to_sleep(p->all->sleep, p->all);
	ft_print(p, "is thinking", YLL);
}

void	*cicle(void	*ptr)
{
	t_philo		*p;
	pthread_t	check;

	p = (t_philo *)ptr;
	p->t_last_meal = now();
	if (pthread_create(&check, 0, life_status, p) != 0)
		return (0);
	pthread_detach(check);
	if (p->id % 2 == 0 && p->all->eat > 1)
		go_to_sleep(p->all->eat * 0.9, p->all);
	while (!p->all->is_dead && \
		(p->dop_end == -1 || (p->dop_start < p->dop_end)))
		go_eat(p);
	return (0);
}

void	ft_start_loop(t_all *all, int i, int j, int k)
{
	void	*philo;

	while (++i < all->philo)
	{
		all->p[i].all = all;
		pthread_mutex_init(&all->forks[i], 0);
		pthread_mutex_init(&all->p[i].eating, 0);
		all->p[i].lft_hand = i;
		all->p[i].rgt_hand = (i + 1) % all->philo;
		all->p[i].id = i + 1;
		all->p[i].eat = 0;
		if (all->n_meal >= 0)
			all->p[i].dop_end = all->n_meal;
		else
			all->p[i].dop_end = -1;
		all->p[i].dop_start = 0;
	}
	while ((++j) < all->philo)
	{
		philo = (void *)(&all->p[j]);
		if (pthread_create(&all->p[j].t, 0, cicle, philo) != 0)
			return ;
	}
	while ((++k) < all->philo)
		pthread_join(all->p[k].t, 0);
}

int	main(int ac, char **av)
{
	int		i;
	t_all	all;

	i = 1;
	if (ft_check_imput(ac, av, &all))
		return (1);
	all.is_dead = 0;
	if (ac == 6 && all.n_meal > 0)
		all.total_meal = all.n_meal * all.philo;
	else
		all.total_meal = -1;
	all.time_start = now();
	ft_start_loop(&all, -1, -1, -1);
	pthread_mutex_destroy(all.forks);
	pthread_mutex_destroy(&all.print);
	pthread_mutex_destroy(&all.dead);
	free(all.forks);
	free(all.p);
	return (0);
}
