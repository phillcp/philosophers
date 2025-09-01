/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiheaton <fiheaton@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 17:36:30 by fheaton-          #+#    #+#             */
/*   Updated: 2025/09/01 18:09:24 by fiheaton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_curr_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

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

int	print_m(t_philo *p, int id, char *str, int monitor)
{
	if (pthread_mutex_lock(&(p->l->w_lock)))
		return (1);
	if (!p->l->end || monitor)
		printf("%lu %d %s\n", get_time(p->l), id, str);
	if (pthread_mutex_unlock(&(p->l->w_lock)))
		return (1);
	return (0);
}
