/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpicchio <tpicchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 11:54:56 by tpicchio          #+#    #+#             */
/*   Updated: 2024/03/20 12:39:09 by tpicchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	int				snacking;
	int				snacks_eaten;
	size_t			last_snack;
	size_t			perish_time;
	size_t			snack_time;
	size_t			nap_time;
	size_t			birth_time;
	int				tot_philo;
	int				max_snacks;
	int				*perished;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*print_lock;
	pthread_mutex_t	*snack_lock;
	pthread_mutex_t	*perish_lock;
}	t_philo;

typedef struct s_monitor
{
	int				perished;
	pthread_mutex_t	perish_lock;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	snack_lock;
	t_philo			*philo;
}	t_monitor;

// philo_life.c
void	ft_snack(t_philo *philo);
void	ft_nap(t_philo *philo);
void	*ft_think_about_life(void *p);

// philosopher.c
int		ft_create_philos(t_monitor *monitor);
int		ft_is_alive(t_philo *philo);

// setup.c
void	ft_setup_monitor(t_monitor *monitor, t_philo *philo);
void	ft_setup_forks(pthread_mutex_t *forks, int n);
void	ft_setup_philo(t_philo *philo, t_monitor *monitor,
			pthread_mutex_t *forks, char **av);

// supervisor.c
void	*ft_supervisor(void *p);
void	ft_print(t_philo *philo, int id, char *msg);

// utils.c
int		ft_my_usleep(size_t time);
size_t	ft_get_time(void);
int		ft_atoi(const char *str);
void	ft_free_all(t_monitor *monitor, pthread_mutex_t *forks, t_philo *philo);

#endif