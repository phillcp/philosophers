/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 22:59:28 by fheaton-          #+#    #+#             */
/*   Updated: 2022/11/07 17:03:18 by fheaton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(int argc, char **argv, t_list **lst)
{
	t_list	*l;
	int		a;

	if (!ft_isnum(argv[1]) || !ft_isnum(argv[2]) || !ft_isnum(argv[3]) \
		|| !ft_isnum(argv[4]) || (argc == 6 && !ft_isnum(argv[5])))
		return (0);
	l = *lst;
	l->nmr_philo = ft_atoi(argv[1]);
	l->t_die = ft_atoi(argv[2]);
	l->t_eat = ft_atoi(argv[3]);
	l->t_sleep = ft_atoi(argv[4]);
	l->philos = ft_calloc(l->nmr_philo, sizeof(t_philo));
	l->forks = ft_calloc(l->nmr_philo, sizeof(pthread_mutex_t));
	if (argc == 6)
		l->nmr_eat = ft_atoi(argv[5]);
	if (!l->philos || !l->forks)
		return (0);
	a = -1;
	while (++a < l->nmr_philo)
		pthread_mutex_init(&l->forks[a], NULL);
	pthread_mutex_init(&l->master, NULL);
	return (1);
}

int	start_threads(t_list *lst)
{
	int	a;

	a = -1;
	while (++a < lst->nmr_philo)
	{
		if (pthread_create(&lst->philos[a].id, NULL, routine, lst))
		{
			printf("couldn't create thread nmr:%d\n", (a + 1));
			return (0);
		}
	}
	return (1);
}

void	clear(t_list *l)
{
	int	a;

	if (!l)
		return ;
	a = -1;
	while (++a < l->nmr_philo)
	{
		pthread_mutex_destroy(&l->forks[a]);
	}
	pthread_mutex_destroy(&l->master);
	free(l->philos);
	free(l->forks);
	free(l);
}

int	join_philos(t_list *l)
{
	int	a;

	a = -1;
	while (1)
	{
		pthread_mutex_lock(&l->master);
		if (l->philo_state == philo_halt)
		{
			pthread_mutex_unlock(&l->master);
			break ;
		}
		pthread_mutex_unlock(&l->master);
	}
	while (++a < l->nmr_philo)
	{
		if (pthread_join(l->philos[a].id, NULL))
			printf("join error.\n");
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_list	*lst;

	if (argc < 5 || argc > 6)
	{
		printf("Nmr of args is wrong\n");
		return (0);
	}
	lst = malloc(sizeof(t_list));
	if (!lst)
		return (0);
	if (!check_args(argc, argv, &lst) || (gettimeofday(&lst->start, NULL) == -1)
		|| !start_threads(lst))
	{
		clear(lst);
		return (1);
	}
	join_philos(lst);
	clear(lst);
	return (0);
}
