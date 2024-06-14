/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpicchio <tpicchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 09:53:42 by tpicchio          #+#    #+#             */
/*   Updated: 2024/06/14 16:41:10 by tpicchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdbool.h>

// Definizione della struttura Filosofo
typedef struct	s_philo
{
	int				id;
	int				tot_philo;
	int 			last_meal;
	int 			tot_meal;
	int 			*status;
	size_t 			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			start;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	// pthread_mutex_t	*print_lock;
	pthread_mutex_t	*stat_mutex;
}				t_philo;

// main.c
void	*ft_calloc(size_t count, size_t size);
void 	*philo_life(void *arg);

// parsing.c
int		ft_check_args(int ac, char **av);
int		ft_check_num(char *str);

// init_data.c
int		ft_init_philo(t_philo *philo, pthread_mutex_t *forks, char **av);

// utils.c
int		ft_print(t_philo *philo, int id, char *msg);
int		ft_usleep(size_t time);
size_t	ft_get_time(void);
int		ft_atoi(const char *str);
void	ft_free_all(pthread_mutex_t *forks, t_philo *philo);

# endif
