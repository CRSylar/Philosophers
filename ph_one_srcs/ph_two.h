/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_two.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cromalde <cromalde@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 11:30:11 by cromalde          #+#    #+#             */
/*   Updated: 2021/04/05 11:51:32 by cromalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_two.h"

int	ft_check_imput(int ac, char **av, t_all *all)
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
		return (printf("Time to sleep can't be neagtive\n"));
	if (ac == 6)
		if ((all->n_meal = ft_atoi(av[5])) < 0)
			return (printf("Number of meal can't be negative\n"));
	if (!(all->p = malloc(sizeof(t_philo) * all->philo)))
		return (printf("Error: memory not allocated\n"));

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
	return (0);
}
