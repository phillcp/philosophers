/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 22:59:28 by fheaton-          #+#    #+#             */
/*   Updated: 2022/03/23 17:06:47 by fheaton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	error(char *error)
{
	ft_putstr_fd("Error\n", 1);
	ft_putstr_fd(error, 1);
	ft_putchar_fd('\n', 1);
	exit(EXIT_FAILURE);
}

int	check_args(int argc, char **argv, t_list **lst)
{
	t_list	*l;

	if (!ft_isnum(argv[1]) || !ft_isnum(argv[2]) || !ft_isnum(argv[3]) \
		|| !ft_isnum(argv[4]) || (argc == 6 && !ft_isnum(argv[5])))
		return (0);
	*lst = ft_calloc(sizeof(t_list), 1);
	l = *lst;
	l->nmr_philo = ft_atoi(argv[1]);
	l->t_die = ft_atoi(argv[2]);
	l->t_eat = ft_atoi(argv[3]);
	l->t_sleep = ft_atoi(argv[4]);
	if(argc == 6)
		l->nmr_eat = ft_atoi(argv[5]);
	if (l->nmr_philo < 1 || l->t_die < 1 || l->t_eat < 1 \
		|| l->t_sleep < 1 || (argc == 6 && l->nmr_eat < 1))
		return (0);
	l->philos = ft_calloc(t->nmr_philo, sizeof(t_philo));
	return (1);
}

int	start_threads(t_list *lst)
{
	int a;
	
	a = -1;
	while (++a != lst->nmr_philo)
	{
		if (pthread_create(&lst->philos[a], NULL, start_routine, lst))
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

int	main(int argc, char **argv)
{
	t_list	*lst;

	if (argc != 5 || argc != 6)
	{
		error("nmr of args is wrong");
		return (0);
	}
	lst = ft_calloc(sizeof(t_list), 1);
	if (!lst)
		return (0);
	if (!check_args(argc, argv, &lst))
	{
		error("invalid args");
		return (0);
	}
	if (gettimeofday(&lst->start, NULL))
	{
		error("couldn't get time of day");
		return (0);
	}
	if (!start_threads(lst))
	{
		error("couldn't create threads");
		clear(lst);
		return (0);
	}


	cada garfo é um mutex


	argc[1] = number_of_philosophers and number of forks
	argc[2] = time_to_die (in milliseconds)
	argc[3] = time_to_eat (in milliseconds)
	argc[4] = time_to_sleep (in milliseconds)
	argc[5] = number_of_times_each_philosopher_must_eat

	output = 
	{
		timestamp_in_ms N has taken a fork
		timestamp_in_ms N is eating
		timestamp_in_ms N is sleeping
		timestamp_in_ms N is thinking
		timestamp_in_ms N died
	}

}
