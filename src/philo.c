/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiheaton <fiheaton@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 16:37:15 by fheaton-          #+#    #+#             */
/*   Updated: 2025/08/25 19:25:22 by fiheaton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(t_list *l)
{
	long	ret;

	gettimeofday(&l->curr, NULL);
	ret = (l->curr.tv_sec - l->start.tv_sec) * 1000
		+ (l->curr.tv_usec - l->start.tv_usec) / 1000;
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

void	one_philo(t_list *l, int id)
{
	printf("%ld %d has taken a fork\n", get_time(l), id + 1);
	tr_usleep(l, id, l->t_die);
	printf("%ld %d died\n", get_time(l), id + 1);
}

int	check_halt(t_list *l)
{
	pthread_mutex_lock(&l->master);
	if (l->philo_state == philo_halt)
			return (pthread_mutex_unlock(&l->master), 0);
	pthread_mutex_unlock(&l->master);
	return (1);
}

void	*routine(void *philos)
{
	t_philo	*p;

	p = (t_philo *)philos;
	if (p->l->nmr_philo == 1)
	{
		one_philo(p->l, p->s_id);
		return (NULL);
	}
	if (((p->s_id + 1) % 2) == 0)
		usleep(p->l->t_eat * 1000);
	while (check_halt(p->l))
	{
		if (finish_eat(p->l, p->s_id))
			return (NULL);
		if (!peat(p->l, p->s_id))
			return (NULL);
		psleep(p->l, p->s_id);
		go_think(p->l, p->s_id);
		if (p->l->nmr_philo % 2 == 1)
			usleep((p->l->t_eat * 2 - p->l->t_sleep) * 1000);
	}
	return (NULL);
}
