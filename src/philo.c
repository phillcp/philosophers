/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiheaton <fiheaton@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 16:37:15 by fheaton-          #+#    #+#             */
/*   Updated: 2025/08/28 16:08:22 by fiheaton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(t_list *l)
{
	long	ret;
	struct timeval curr;

	gettimeofday(&curr, NULL);
	ret = (curr.tv_sec - l->start.tv_sec) * 1000
		+ (curr.tv_usec - l->start.tv_usec) / 1000;
	return (ret);
}

static int	finish_eat(t_list *l, int id)
{
	pthread_mutex_lock(&l->meat_lock);
	if (l->philos[id].eat_count == l->nmr_eat)
	{
		pthread_mutex_unlock(&l->meat_lock);
		return (1);
	}
	pthread_mutex_unlock(&l->meat_lock);
	return (0);
}

int	check_halt(t_list *l)
{
	pthread_mutex_lock(&(l->w_lock));
	if (l->end)
		return (pthread_mutex_unlock(&l->w_lock), 0);
	pthread_mutex_unlock(&(l->w_lock));
	return (1);
}

void	*routine(void *philos)
{
	t_philo	*p;

	p = (t_philo *)philos;
	if (((p->s_id + 1) % 2) == 0)
		usleep(p->l->t_eat * 1000);
	while (1)
	{
		if (finish_eat(p->l, p->s_id))
			return (NULL);
		if (!peat(p, p->s_id))
		{
			pthread_mutex_lock(&p->l->w_lock);
			p->l->end = 1;
			return (pthread_mutex_unlock(&p->l->w_lock), NULL);
		}
		psleep(p, p->s_id);
		if (!check_halt(p->l))
			return (NULL);
		if (p->l->nmr_philo % 2 == 1)
			usleep((p->l->t_eat * 2 - p->l->t_sleep) * 1000);
	}
	return (NULL);
}

void	init_philo(t_list *lst, int a)
{
	lst->philos[a].s_id = a;
	lst->philos[a].l = lst;
	lst->philos[a].last_eat = get_time(lst);
	lst->philos[a].finish_eat = 0;
	lst->philos[a].l_fork = a;
	lst->philos[a].r_fork = (a + 1) % lst->nmr_philo;
}
