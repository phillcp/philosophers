/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiheaton <fiheaton@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 21:44:44 by fheaton-          #+#    #+#             */
/*   Updated: 2025/08/28 14:12:28 by fiheaton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

enum e_philo_state
{
	philo_halt = 0,
	philo_running = 1
};

typedef struct s_philo
{
	pthread_t		id;
	struct s_list	*l;
	int				s_id;
	int				l_fork;
	int				r_fork;
	long long		last_eat;
	int				eat_count;
	int				finish_eat;
}				t_philo;

typedef struct s_list
{
	int					nmr_philo;
	int					t_die;
	int					t_eat;
	int					t_sleep;
	int					nmr_eat;
	int					claim;
	struct timeval		start;
	struct timeval		curr;
	int					eaten;
	int					end;
	enum e_philo_state	philo_state;
	pthread_t			watcher;
	t_philo				philos[200];
	pthread_mutex_t		forks[200];
	pthread_mutex_t		master;
	pthread_mutex_t		w_lock;
	pthread_mutex_t		meat_lock;
}						t_list;

/*
**				main
*/

int			join_philos(t_list *l);
void		clear(t_list *l);
int			start_threads(t_list *lst);
int			check_args(int argc, char **argv, t_list **lst);
int			print_m(t_philo *p, int id, char *str, int monitor);

/*
**				philo
*/

void		*routine(void *lst);
long		get_time(t_list *l);
void		init_philo(t_list *lst, int a);

/*
**				philo_extra
*/

void		psleep(t_philo *l, int id);
int			peat(t_philo *p, int id);

/*
**				monitor
*/

void		*monitor(void *arg);
int			check_state(t_list *l);
void		init_table(t_list *l, char **argv);

/*
**				extra
*/

int			ft_atoi(const char *str);
int			ft_isnum(char *str);
int			ft_isdigit(int c);

/*
**				extra2
*/

void		*ft_calloc(size_t nmemb, size_t size);
void		*ft_memset(void *str, int c, size_t n);

#endif
