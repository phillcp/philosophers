/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_extra.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiheaton <fiheaton@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 17:20:33 by fheaton-          #+#    #+#             */
/*   Updated: 2025/08/28 16:25:18 by fiheaton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	get_forks(t_philo *p, int id)
{
	int		a;

	if ((id + 1) % 2 == 1)
		a = p->l_fork;
	else
		a = p->r_fork;
	pthread_mutex_lock(&p->l->forks[a]);
	print_m(p, id + 1, "has taken a fork", 0);
	if (p->l->nmr_philo == 1)
		return (pthread_mutex_unlock(&(p->l->forks[a])), 0);
	if ((id + 1) % 2 == 1)
		a = p->r_fork;
	else
		a = p->l_fork;
	pthread_mutex_lock(&p->l->forks[a]);
	print_m(p, id + 1, "has taken a fork", 0);
	return (1);
}

int	peat(t_philo *p, int id)
{
	if (!get_forks(p, id))
		return (0);
	pthread_mutex_lock(&p->l->master);
	p->last_eat = get_time(p->l);
	pthread_mutex_unlock(&p->l->master);
	print_m(p, id + 1, "is eating", 0);
	usleep(p->l->t_eat * 1000);
	p->eat_count += 1;
	pthread_mutex_lock(&p->l->meat_lock);
	if (!p->finish_eat && (p->eat_count == p->l->nmr_eat))
		p->finish_eat = 1;
	pthread_mutex_unlock(&p->l->meat_lock);
	pthread_mutex_unlock(&p->l->forks[id]);
	pthread_mutex_unlock(&p->l->forks[(id + 1) % p->l->nmr_philo]);
	return (1);
}

void	psleep(t_philo *p, int id)
{
	print_m(p, id + 1, "is sleeping", 0);
	usleep(p->l->t_sleep * 1000);
	print_m(p, id + 1, "is thinking", 0);
}
