/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiheaton <fiheaton@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 16:37:15 by fheaton-          #+#    #+#             */
/*   Updated: 2025/09/01 18:11:45 by fiheaton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(t_list *l)
{
	long	ret;

	ret = get_curr_time() - l->start;
	return (ret);
}

static int	finish_eat(t_philo *p)
{
	pthread_mutex_lock(&p->l->meat_lock);
	if (p->finish_eat)
		return (pthread_mutex_unlock(&p->l->meat_lock), 1);
	return (pthread_mutex_unlock(&p->l->meat_lock), 0);
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
	if (((p->s_id) % 2) == 0)
		usleep(p->l->t_eat * 1000);
	while (1)
	{
		if (finish_eat(p))
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
	lst->philos[a].s_id = a + 1;
	lst->philos[a].l = lst;
	lst->philos[a].finish_eat = 0;
	lst->philos[a].l_fork = a;
	lst->philos[a].r_fork = (a + 1) % lst->nmr_philo;
}
