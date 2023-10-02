/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachera <mvachera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 16:44:31 by mvachera          #+#    #+#             */
/*   Updated: 2023/10/02 02:40:04 by mvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_arg(int ac, char **av)
{
	int			i;
	long int	tmp;

	i = 1;
	while (i < ac)
	{
		if (!av[i] || !*av[i])
			return (0);
		if (check(av[i]) == 0)
			return (0);
		tmp = ft_atoi(av[i]);
		if (tmp <= 0 || tmp > 2147483647)
			return (0);
		i++;
	}
	return (1);
}

int	check(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

long int	ft_atoi(char *nptr)
{
	long int	i;
	long int	num;

	i = 0;
	num = 0;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		num = num * 10 + (nptr[i] - '0');
		if (num > INT_MAX || num < INT_MIN)
			return (2147483648);
		i++;
	}
	return (num);
}
