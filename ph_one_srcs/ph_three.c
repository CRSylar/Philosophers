/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_three.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cromalde <cromalde@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 11:30:11 by cromalde          #+#    #+#             */
/*   Updated: 2021/04/05 18:10:39 by cromalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_three.h"

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
	all->p.pid = malloc(sizeof(pid_t) * all->philo);
	if (!all->p.pid)
		return (printf("Error: memory not allocated\n"));
	sem_unlink("print");
	sem_unlink("dead");
	sem_unlink("forks");
	sem_unlink("eating");
	all->print = sem_open("eating", O_CREAT | O_EXCL, 0777, 1);
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
	p->m_start++;
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
		exit(1);
	pthread_detach(check);
	if (p->id % 2 == 0)
		go_to_sleep(p->all->eat * 0.9, p->all);
	while (!p->all->is_dead && (p->m_end == -1 || p->m_start < p->m_end))
		go_eat(p);
	if ((!p->all->is_dead) && (p->m_end != -1) && (p->m_start == p->m_end))
		exit(2);
	return (0);
}

void	ft_start_loop(t_all *all, int i, int j, int check)
{
	all->status = 0;
	all->p.m_start = 0;
	all->p.m_end = -1;
	if (all->n_meal >= 0)
		all->p.m_end = all->n_meal;
	while ((++i) < all->philo)
	{
		all->p.pid[i] = fork();
		if ((all->p.pid[i] < 0) && printf("Cannot fork!\n"))
			return ;
		else if (all->p.pid[i] == 0)
		{
			all->p.id = i + 1;
			cicle((void *)(&all->p));
		}
	}
	while (1)
	{
		waitpid(-1, &all->status, 0);
		if ((WEXITSTATUS(all->status) == 1) || (WEXITSTATUS(all->status) == 2 && \
			(++check == all->philo)))
			break ;
	}
	while ((++j) < all->philo)
		kill(all->p.pid[j], SIGKILL);
}

int	main(int ac, char **av)
{
	t_all	all;

	all.p.all = &all;
	if (ft_check_imput(ac, av, &all))
		return (1);
	all.is_dead = 0;
	all.time_start = now();
	ft_start_loop(&all, -1, -1, 0);
	sem_close(all.dead);
	sem_close(all.print);
	sem_close(all.forks);
	sem_close(all.p.eating);
	sem_unlink("eating");
	sem_unlink("print");
	sem_unlink("forks");
	sem_unlink("dead");
	free(all.p.pid);
	return (0);
}
