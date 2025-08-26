/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiheaton <fiheaton@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 21:44:44 by fheaton-          #+#    #+#             */
/*   Updated: 2025/08/26 13:49:18 by fiheaton         ###   ########.fr       */
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
	long long		last_eat;
	int				eat_count;
}				t_philo;

typedef struct s_watch
{
	pthread_t	id;
}				t_watcher;

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
	int					died;
	enum e_philo_state	philo_state;
	t_watcher			*watcher;
	t_philo				*philos;
	pthread_mutex_t		*forks;
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

/*
**				philo
*/

void		*routine(void *lst);
long		get_time(t_list *l);

/*
**				philo_extra
*/

void		psleep(t_list *l, int id);
int			peat(t_list *l, int id);
void		tr_usleep(t_list *l, int id, long t);

/*
**				monitor
*/

void		*monitor(void *arg);
int			check_state(t_list *l);
void		init_table(t_list *l, char **argv);

/*
**				extra
*/

void		err_exit(char *err, t_list *lst);
int			ft_atoi(const char *str);
int			ft_isnum(char *str);
int			ft_isdigit(int c);

/*
**				extra2
*/

void		*ft_calloc(size_t nmemb, size_t size);
void		*ft_memset(void *str, int c, size_t n);
void		go_get_fork(t_list *l, int id);
void		go_think(t_list *l, int id);
void		go_eat(t_list *l, int id);

#endif
