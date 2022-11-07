/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 22:10:59 by fheaton-          #+#    #+#             */
/*   Updated: 2022/11/07 17:30:35 by fheaton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	ft_isnum(char *str)
{
	int	a;

	a = -1;
	while (str[++a])
	{
		if (!ft_isdigit(str[a]))
			return (0);
	}
	return (1);
}

static int	ft_isspace(int c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

int	ft_atoi(const char *str)
{
	int	a;
	int	b;
	int	c;

	a = 0;
	b = 1;
	c = 0;
	while (ft_isspace(str[a]))
		a++;
	if (str[a] == '+')
		a++;
	else if (str[a] == '-')
	{
		b *= -1;
		a++;
	}
	while (ft_isdigit(str[a]))
	{
		c = c * 10 + str[a] - '0';
		a++;
	}
	return (c *= b);
}
