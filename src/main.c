/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 22:59:28 by fheaton-          #+#    #+#             */
/*   Updated: 2022/03/19 00:37:12 by fheaton-         ###   ########.fr       */
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
		|| l->t_sleep < 1 || (argc == 6 && t->nmr_eat < 1))
		return (0);
	t->philos = ft_calloc(t->nmr_philo, sizeof(t_philo));
	return (1);
}

int	start(t_list *lst)
{
	int a;
	
	a = -1;
	while (++a != lst->nmr_philo)
	{
		if (pthread_create(&t->philos[a], NULL, start_routine, lst))
		{
			printf("couldn't create thread nmr:%d\n", (a + 1));
			return (0);
		}
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_list	*lst;

	if (argc != 5 || argc != 6)
	{
		error("nmr of args is wrong")
		return (0);
	}
	if (!check_args(argc, argv, &lst))
	{
		error("invalid args");
		return (0);
	}
	if (!start(lst))
		return (0);

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
