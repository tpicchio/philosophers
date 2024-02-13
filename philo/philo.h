/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpicchio <tpicchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 11:54:56 by tpicchio          #+#    #+#             */
/*   Updated: 2024/02/13 10:11:26 by tpicchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_monitor
{
	int				perished;
	pthread_mutex_t	perish_lock;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	snack_lock;
	t_philo			*philo;
}	t_monitor;

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



#endif