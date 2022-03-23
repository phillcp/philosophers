/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 21:44:44 by fheaton-          #+#    #+#             */
/*   Updated: 2022/03/19 00:37:43 by fheaton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <pthread.h>

typedef struct s_philo
{
	pthread_t	id;
	long long	last_eat;
	int			eat_count;
}				t_philo

typedef struct s_list
{
	int			nmr_philo;
	int			t_die;
	int			t_eat;
	int			t_sleep;
	int			nmr_eat;
	t_philo 	*philos;
}				t_list

#endif
