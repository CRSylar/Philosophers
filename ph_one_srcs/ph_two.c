/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_two.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cromalde <cromalde@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 11:30:11 by cromalde          #+#    #+#             */
/*   Updated: 2021/04/05 18:12:17 by cromalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_two.h"

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
	if (!all->p)
		return (printf("Error: memory not allocated\n"));
	sem_unlink("print");
	sem_unlink("dead");
	sem_unlink("forks");
	all->print = sem_open("print", O_CREAT | O_EXCL, 0777, 1);
	all->dead = sem_open("dead", O_CREAT | O_EXCL, 0777, 1);
	all->forks = sem_open("forks", O_CREAT | O_EXCL, 0777, all->philo);
	return (0);
}

void	go_eat(t_philo *p)
{
	sem_wait(p->all->forks);
	ft_print(p, "has taken a fork", YLL);
	sem_wait(p->all->forks);
	ft_print(p, "has taken a fork", YLL);
	sem_wait(p->eating);
	p->t_last_meal = now();
	ft_print(p, "is eating", GRN);
	p->dop_start++;
	if (p->all->total_meal > 0)
		p->all->total_meal -= 1;
	go_to_sleep(p->all->eat, p->all);
	sem_post(p->eating);
	sem_post(p->all->forks);
	sem_post(p->all->forks);
	ft_print(p, "is sleeping", YLL);
	go_to_sleep(p->all->sleep, p->all);
	ft_print(p, "is thinking", YLL);
}

void	*cicle(void *ptr)
{
	t_philo		*p;
	pthread_t	check;

	p = (t_philo *)ptr;
	p->t_last_meal = now();
	if (pthread_create(&check, 0, life_status, p) != 0)
		return (0);
	pthread_detach(check);
	if (p->id % 2 == 0)
		go_to_sleep(p->all->eat * 0.9, p->all);
	while (!p->all->is_dead && (p->dop_end == -1 || p->dop_start < p->dop_end))
		go_eat(p);
	return (0);
}

void	ft_start_loop(t_all *all, int i, int j, int k)
{
	void	*philo;

	while ((++i) < all->philo)
	{
		all->p[i].all = all;
		all->p[i].eating = sem_open("eating", O_CREAT | O_EXCL, 0777, 1);
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
	i = -1;
	while ((++i) < all->philo)
		k = sem_close(all->p[i].eating) + sem_unlink("eating");
}

int	main(int ac, char **av)
{
	t_all	all;

	if (ft_check_imput(ac, av, &all))
		return (1);
	all.is_dead = 0;
	if (ac == 6 && all.n_meal > 0)
		all.total_meal = all.n_meal * all.philo;
	else
		all.total_meal = -1;
	all.time_start = now();
	ft_start_loop(&all, -1, -1, -1);
	sem_close(all.dead);
	sem_close(all.print);
	sem_close(all.forks);
	sem_unlink("print");
	sem_unlink("forks");
	sem_unlink("dead");
	free(all.p);
	return (0);
}
