/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_one.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cromalde <cromalde@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 19:49:28 by cromalde          #+#    #+#             */
/*   Updated: 2021/04/03 17:27:59 by cromalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_one.h"

int		ft_check_imput(int ac, char **av, t_all *all)
{
	if (ac < 5 || ac > 6)
		return (printf("Wrong number of arguments\n"));
	if ((all->philo = ft_atoi(av[1])) < 1)
		return (printf("At least 1 Philo needed!\n"));
	if ((all->die = ft_atoi(av[2])) < 0)
		return (printf("Time to die can't be negative\n"));
	if ((all->eat = ft_atoi(av[3])) < 0)
		return (printf("Time to eat can't be negative\n"));
	if ((all->sleep = ft_atoi(av[4])) < 0)
		return (printf("Time to sleep can't be negative\n"));
	if (ac == 6)
		if ((all->n_meal = ft_atoi(av[5] < 0)))
			return (printf("Number of meals can't be negative\n"));
	if (!(all->p = malloc(sizeof(t_philo) * all->philo)))
		return (printf("Error: memory not allocated\n"));
	if (!(all->forks = malloc(sizeof(pthread_mutex_t) * all->philo)))
		return (printf("Error: memory not allocated\n"));
	return (0);
}

void	go_eat(t_philo *p)
{
	pthread_mutex_lock(&p->all->forks[p->rgt_hand]);
	ft_print(p, "has taken a fork");
	pthread_mutex_lock(&p->all->forks[p->lft_hand]);
	ft_print(p, "has taken a fork");
	pthread_mutex_lock(&p->eating);
	p->t_last_meal = now();
	ft_print(p, "is eating");
	p->dop_start++;
	if (p->all->total_meal > 0)
		p->all->total_meal -= 1;
	go_to_sleep(p->all->eat, p->all);
	pthread_mutex_unlock(&p->eating);
	pthread_mutex_unlock(&p->all->forks[p->rgt_hand]);
	pthread_mutex_unlock(&p->all->forks[p->lft_hand]);
	ft_print(p, "is sleeping");
	go_to_sleep(p->all->sleep, p->all);
	ft_print(p, "is thinking");
}

void	*cicle(void	*ptr)
{
	t_philo		*p;
	pthread_t	check;

	p = (t_philo*)ptr;
	p->t_last_meal = now();
	if (pthread_create(&check, 0, life_status, p) != 0)
		return (0);
	pthread_detach(check);
	if (p->id % 2 == 0 && p->all->eat > 1)
		go_to_sleep(p->all->eat * 0.9, p->all);
	while (!p->all->is_dead && (p->dop_end == -1 || (p->dop_end > p->dop_start)))
		go_eat(p);
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
		if (all->n_meal > 0)
			all->p[i].dop_end = all->n_meal;
		else
			all->p[i].dop_end = -1;
	}
	while ((++j) < all->philo)
	{
		philo = (void*)(&all->p[i]);
		if (pthread_create(&all->p[j].t, 0, cicle, philo) != 0)
			return ;
	}
	while ((++k) < all->philo)
		pthread_join(all->p[k].t, 0);
}

int		main(int ac, char **av)
{
	int 	i;
	t_all	all;

	i = 1;
	if (ft_check_imput(ac, av, &all))
		return (1);
	all.time_start = now();
	ft_start_loop(&all, -1, -1, -1);
	return (0);
}
