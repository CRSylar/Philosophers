/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_one.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cromalde <cromalde@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 19:49:28 by cromalde          #+#    #+#             */
/*   Updated: 2021/03/30 17:17:44 by cromalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_takefork()
{

}

void	ft_start_loop(t_all *all)
{
	int	i;
	int fork;
	pthread_t philo[all->philo];

	fork = all->philo;
	i = 0;
	while (i < all->philo)
	{
		pthread_mutex_init(&(all->forks), NULL);
		i++;
	}
}

int		main(int ac, char **av)
{
	int 	i;
	t_all	all;

	i = 1;
	if (ac < 5 || ac > 6)
		return (printf("Wrong number of arguments\n"));
	if ((all.philo = ft_atoi(av[1])) < 1)
		return (printf("At least 1 Philo needed!\n"));
	if ((all.die = ft_atoi(av[2])) < 0)
		return (printf("Time to die can't be negative\n"));
	if ((all.eat = ft_atoi(av[3])) < 0)
		return (printf("Time to eat can't be negative\n"));
	if ((all.sleep = ft_atoi(av[4])) < 0)
		return (printf("Time to sleep can't be negative\n"));
	if (ac == 6)
		if ((all.meals = ft_atoi(av[5] < 0)))
			return (printf("Number of meals can't be negative\n"));
	ft_start_loop(&all);
	return (0);
}
