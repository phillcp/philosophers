/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiheaton <fiheaton@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 17:36:30 by fheaton-          #+#    #+#             */
/*   Updated: 2025/08/25 17:59:39 by fiheaton         ###   ########.fr       */
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

void	go_eat(t_list *l, int id)
{
	if (pthread_mutex_lock(&l->w_lock))
		return ;
	if (l->philo_state == philo_running)
		printf("%lld %d is eating\n", l->philos[id].last_eat, id + 1);
	pthread_mutex_unlock(&l->w_lock);
}

void	go_get_fork(t_list *l, int id)
{
	if (pthread_mutex_lock(&l->w_lock))
		return ;
	if (l->philo_state == philo_running)
		printf("%ld %d has taken a fork\n", get_time(l), id + 1);
	pthread_mutex_unlock(&l->w_lock);
}

void	go_think(t_list *l, int id)
{
	if (pthread_mutex_lock(&l->w_lock))
		return ;
	if (l->philo_state == philo_running)
		printf("%ld %d is thinking\n", get_time(l), id + 1);
	pthread_mutex_unlock(&l->w_lock);
}
