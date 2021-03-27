/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cromalde <cromalde@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 21:20:10 by cromalde          #+#    #+#             */
/*   Updated: 2021/03/27 21:20:48 by cromalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int		ft_atoi(const char *nptr)
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