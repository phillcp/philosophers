/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_extra.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiheaton <fiheaton@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 17:20:33 by fheaton-          #+#    #+#             */
/*   Updated: 2025/08/25 19:07:04 by fiheaton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	tr_usleep(t_list *l, int id, long t)
{
	long	start;
	long	curr;
	long	sleep;

	start = get_time(l);
	curr = start;
	sleep = 100;
	while ((start + t) > curr)
	{
		curr = get_time(l);
		(((curr + 50) < (start + t)) && (sleep = 50));
		if ((curr + sleep) < (start + t)
			&& curr + sleep - l->philos[id].last_eat < l->t_die)
			usleep(sleep);
		else if (sleep - 10 > 0)
			sleep -= 10;
		curr = get_time(l);
	}
}

static int	get_forks(t_list *l, int id)
{
	int		a;

	if (id % 2 == 1)
		a = id;
	else
		a = (id + 1) % l->nmr_philo;
	pthread_mutex_lock(&l->forks[a]);
	go_get_fork(l, id);
	if (id % 2 == 1)
		a = (id + 1) % l->nmr_philo;
	else
		a = id;
	pthread_mutex_lock(&l->forks[a]);
	go_get_fork(l, id);
	return (1);
}

int	peat(t_list *l, int id)
{
	get_forks(l, id);
	l->philos[id].last_eat = get_time(l);
	go_eat(l, id);
	usleep(l->t_eat * 1000);
	pthread_mutex_lock(&l->meat_lock);
	if (l->nmr_eat && ++l->philos[id].eat_count == l->nmr_eat)
		l->eaten++;
	pthread_mutex_unlock(&l->meat_lock);
	pthread_mutex_unlock(&l->forks[id]);
	pthread_mutex_unlock(&l->forks[(id + 1) % l->nmr_philo]);
	return (1);
}

void	psleep(t_list *l, int id)
{
	long	time;

	time = get_time(l);
	if (pthread_mutex_lock(&l->w_lock))
		return ;
	if (l->philo_state == philo_running)
		printf("%ld %d is sleeping\n", time, id + 1);
	pthread_mutex_unlock(&l->w_lock);
	usleep(l->t_sleep * 1000);
}
