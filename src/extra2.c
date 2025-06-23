/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 17:36:30 by fheaton-          #+#    #+#             */
/*   Updated: 2025/06/02 16:37:10 by fheaton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_memset(void *str, int c, size_t n)
{
	unsigned char	*s;
	size_t			a;

	a = (size_t)(-1);
	s = (unsigned char *)str;
	while (++a < n)
		s[a] = c;
	return (str);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*arr;

	if (size != 0)
	{
		arr = malloc(nmemb * size);
		if (!arr)
			return (NULL);
		ft_memset(arr, 0, size * nmemb);
	}
	else
	{
		arr = malloc(0);
		if (!arr)
			return (NULL);
	}
	return ((void *)arr);
}

int	go_get_fork(t_list *l, int id)
{
	pthread_mutex_lock(&l->master);
	if (l->philo_state == philo_halt)
		return (pthread_mutex_unlock(&l->master) && 0);
	printf("%ld %d has taken a fork\n", get_time(l), id + 1);
	pthread_mutex_unlock(&l->master);
	return (1);
}

int	go_think(t_list *l, int id)
{
	pthread_mutex_lock(&l->master);
	if (l->philo_state == philo_halt)
		return (pthread_mutex_unlock(&l->master) && 0);
	printf("%ld %d is thinking\n", get_time(l), id + 1);
	pthread_mutex_unlock(&l->master);
	return (1);
}
