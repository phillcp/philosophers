/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiheaton <fiheaton@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 22:59:28 by fheaton-          #+#    #+#             */
/*   Updated: 2025/08/28 19:25:50 by fiheaton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(int argc, char **argv, t_list **lst)
{
	t_list	*l;
	int		a;

	if (!ft_isnum(argv[1]) || !ft_isnum(argv[2]) || !ft_isnum(argv[3])
		|| !ft_isnum(argv[4]) || (argc == 6 && !ft_isnum(argv[5])))
		return (0);
	l = *lst;
	init_table(l, argv);
	if (argc == 6)
		l->nmr_eat = ft_atoi(argv[5]);
	a = -1;
	while (++a < l->nmr_philo)
	{
		init_philo(l, a);
		pthread_mutex_init(&l->forks[a], NULL);
	}
	pthread_mutex_init(&l->master, NULL);
	pthread_mutex_init(&l->w_lock, NULL);
	pthread_mutex_init(&l->meat_lock, NULL);
	return (1);
}

int	start_threads(t_list *lst)
{
	int	a;

	a = -1;
	gettimeofday(&lst->start, NULL);
	pthread_create(&lst->watcher, NULL, monitor, (void *)lst);
	while (++a < lst->nmr_philo)
	{
		pthread_mutex_lock(&lst->master);
		lst->philos[a].last_eat = get_time(lst);
		if (pthread_create(&lst->philos[a].id, NULL, routine,
				(void *)&lst->philos[a]))
		{
			printf("couldn't create thread nmr:%d\n", (a + 1));
			return (0);
		}
		pthread_mutex_unlock(&lst->master);
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
	if (l->nmr_philo)
	{
		pthread_mutex_destroy(&l->master);
		pthread_mutex_destroy(&l->w_lock);
		pthread_mutex_destroy(&l->meat_lock);
	}
	free(l);
}

int	join_philos(t_list *l)
{
	int	a;

	a = -1;
	while (++a < l->nmr_philo)
	{
		if (pthread_join(l->philos[a].id, NULL))
			return (printf("join error.\n"));
	}
	if (pthread_join(l->watcher, NULL) != 0)
		return (printf("join error.\n"));
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
	lst = ft_calloc(sizeof(t_list), 1);
	if (!lst)
		return (0);
	if (!check_args(argc, argv, &lst) || !start_threads(lst))
	{
		clear(lst);
		printf("Args wrong\n");
		return (1);
	}
	join_philos(lst);
	clear(lst);
	return (0);
}
