/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiheaton <fiheaton@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 12:44:18 by fiheaton          #+#    #+#             */
/*   Updated: 2025/08/28 19:01:52 by fiheaton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_table(t_list *l, char **argv)
{
	l->nmr_philo = ft_atoi(argv[1]);
	l->t_die = ft_atoi(argv[2]);
	l->t_eat = ft_atoi(argv[3]);
	l->t_sleep = ft_atoi(argv[4]);
	l->nmr_eat = -1;
	l->end = 0;
}

int	check_eat(t_list *l)
{
	int	i;

	i = -1;
	while (++i < l->nmr_philo)
	{
		pthread_mutex_lock(&l->meat_lock);
		if (!(l->philos[i].finish_eat) && (l->nmr_eat != 0))
			return (pthread_mutex_unlock(&l->meat_lock), 0);
		pthread_mutex_unlock(&l->meat_lock);
	}
	return (1);
}

int	check_state(t_list *l)
{
	long	time;
	int		i;

	time = get_time(l);
	i = -1;
	while (++i < l->nmr_philo)
	{
		pthread_mutex_lock(&l->master);
		if (time - l->philos[i].last_eat >= l->t_die && time != 0)
		{
			print_m(&(l->philos[i]), i + 1, "died", 1);
			pthread_mutex_lock(&l->w_lock);
			l->end = 1;
			pthread_mutex_unlock(&l->master);
			return (pthread_mutex_unlock(&l->w_lock), 0);
		}
		pthread_mutex_unlock(&l->master);
	}
	return (1);
}

void	*monitor(void *list)
{
	t_list	*l;

	l = (t_list *)list;
	while (1)
	{
		if (!check_state(l))
			return (NULL);
		if (l->nmr_eat != -1 && check_eat(l))
		{
			pthread_mutex_lock(&l->w_lock);
			l->end = 1;
			return (pthread_mutex_unlock(&l->w_lock), NULL);
		}
		usleep(100);
	}
	return (NULL);
}
