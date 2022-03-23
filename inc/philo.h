/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 21:44:44 by fheaton-          #+#    #+#             */
/*   Updated: 2022/03/23 17:02:32 by fheaton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <pthread.h>
# include <time.h>

typedef struct s_philo
{
	pthread_t	id;
	long long	last_eat;
	int			eat_count;
}				t_philo;

typedef struct s_list
{
	int				nmr_philo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				nmr_eat;
	struct timeval	start;
	struct timeval	curr;
	t_philo 		*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*master;
}					t_list;

#endif
