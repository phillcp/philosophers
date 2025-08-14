/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiheaton <fiheaton@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 16:37:15 by fheaton-          #+#    #+#             */
/*   Updated: 2025/08/14 19:59:22 by fiheaton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	self_id(t_list *l)
{
	int	a;

	pthread_mutex_lock(&l->master);
	a = l->claim;
	l->claim++;
	pthread_mutex_unlock(&l->master);
	return (a);
}

int	check_state(t_list *l, int id)
{
	long	time;

	pthread_mutex_lock(&l->master);
	time = get_time(l);
	if (l->eaten == l->nmr_philo)
	{
		if (l->philo_state != philo_halt)
			l->philo_state = philo_halt;
		pthread_mutex_unlock(&l->master);
		return (0);
	}
	if ((time - l->philos[id].last_eat) > l->t_die)
	{
		if (l->philo_state != philo_halt)
		{
			printf("%ld %d died\n", get_time(l), id + 1);
			l->philo_state = philo_halt;
			l->died = 1;
		}
		pthread_mutex_unlock(&l->master);
		return (0);
	}
	pthread_mutex_unlock(&l->master);
	return (1);
}

long	get_time(t_list *l)
{
	long	ret;

	gettimeofday(&l->curr, NULL);
	ret = (l->curr.tv_sec - l->start.tv_sec) * 1000
		+ (l->curr.tv_usec - l->start.tv_usec) / 1000;
	return (ret);
}

static int	check_status(t_list *l)
{
	pthread_mutex_lock(&l->master);
	if (l->philo_state == philo_halt)
	{
		pthread_mutex_unlock(&l->master);
		return (0);
	}
	pthread_mutex_unlock(&l->master);
	return (1);
}

void	*routine(void *lst)
{
	t_list	*l;
	int		id;

	l = (t_list *)lst;
	id = self_id(l);
	l->philo_state = philo_running;
	if (l->nmr_philo == 1)
	{
		printf("%ld %d has taken a fork\n", get_time(l), id + 1);
		tr_usleep(l, id, l->t_die);
		printf("%ld %d died\n", get_time(l), id + 1);
		return (NULL);
	}
	if (id + 1 % 2 == 0)
		usleep(l->t_eat);
	while (1)
	{
		if (!check_status(l) || !peat(l, id))
			break ;
		if (!check_status(l) || !psleep(l, id))
			break ;
		if (!go_think(l, id) || !check_state(l, id))
			break ;
	}
	return (lst);
}
