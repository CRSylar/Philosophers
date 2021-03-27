/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_one.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cromalde <cromalde@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 19:49:28 by cromalde          #+#    #+#             */
/*   Updated: 2021/03/27 21:22:52 by cromalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int main    (int ac, char **av)
{
	int 	i;
	t_all	all;

	i = 1;
	if (ac < 5 || ac > 6)
		return (printf("Wrong number of arguments\n"));
	if ((all.philo = ft_atoi(av[1])) < 1)
		return (printf("Inserisci almeno 1 filosofo !\n"));
	if ((all.die = ft_atoi(av[2])) < 0)
		return (printf("Time to die can't be negative\n"));
	if ((all.eat = ft_atoi(av[3])) < 0)
		return (printf("Time to eat can't be negative\n"));
	if ((all.sleep = ft_atoi(av[4])) < 0)
		return (printf("Time to sleep can't be negative\n"));
	
}
