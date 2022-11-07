/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_extra.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 17:20:33 by fheaton-          #+#    #+#             */
/*   Updated: 2022/11/07 18:01:19 by fheaton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	tr_usleep(t_list *l, int id, long t)
{
	long	start;
	long	curr;
	long	sleep;

	start = get_time(l);
	curr = start;
	sleep = 100;
	while ((start + t) > curr)
	{
		if (!check_state(l, id))
			break ;
		curr = get_time(l);
		(((curr + 50) < (start + t)) && (sleep = 50));
		if ((curr + sleep) < (start + t)
			&& curr + sleep - l->philos[id].last_eat < l->t_die)
			usleep(sleep);
		else
			sleep -= 10;
		curr = get_time(l);
	}
	return (1);
}

static int	can_wait(t_list *l, int id)
{
	if (l->philos[id].last_eat > 0 && l->t_eat * 2 > l->t_die)
		return (0);
	if (l->philos[id].last_eat > 0 && l->t_eat * 3 > l->t_die
		&& l->nmr_philo == 3)
		return (0);
	return (1);
}

static int	get_forks(t_list *l, int id)
{
	int		a;
	int		bin;

	(void)bin;
	if (!can_wait(l, id) && tr_usleep(l, id, l->t_die))
		return (0);
	bin = (((id % 2) && (a = id)) || (a = (id + 1) % l->nmr_philo));
	pthread_mutex_lock(&l->forks[a]);
	if (!check_state(l, id))
		return (pthread_mutex_unlock(&l->forks[a]) && 0);
	printf("%ld %d has taken a fork\n", get_time(l), id + 1);
	bin = (((id % 2) && ((a = (id + 1) % l->nmr_philo) || 1)) || (a = id));
	pthread_mutex_lock(&l->forks[a]);
	if (!check_state(l, id))
	{
		pthread_mutex_unlock(&l->forks[id]);
		pthread_mutex_unlock(&l->forks[(id + 1) % l->nmr_philo]);
		return (0);
	}
	printf("%ld %d has taken a fork\n", get_time(l), id + 1);
	return (1);
}

int	peat(t_list *l, int id)
{
	if (!get_forks(l, id))
		return (0);
	pthread_mutex_lock(&l->master);
	(!l->start_parity) && (((id % 2) && (l->start_parity = 1))
		|| (l->start_parity = 2));
	pthread_mutex_unlock(&l->master);
	l->philos[id].last_eat = get_time(l);
	printf("%lld %d is eating\n", l->philos[id].last_eat, id + 1);
	tr_usleep(l, id, l->t_eat);
	if (l->nmr_eat != -1 && ++l->philos[id].eat_count == l->nmr_eat)
	{
		pthread_mutex_lock(&l->master);
		l->eaten++;
		pthread_mutex_unlock(&l->master);
	}
	pthread_mutex_unlock(&l->forks[id]);
	pthread_mutex_unlock(&l->forks[(id + 1) % l->nmr_philo]);
	if (!check_state(l, id))
		return (0);
	return (1);
}

int	psleep(t_list *l, int id)
{
	long	time;

	time = get_time(l);
	printf("%ld %d is sleeping\n", time, id + 1);
	tr_usleep(l, id, l->t_sleep);
	if (!check_state(l, id))
		return (0);
	return (1);
}
