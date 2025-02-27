/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpicchio <tpicchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 09:53:42 by tpicchio          #+#    #+#             */
/*   Updated: 2024/11/14 10:50:38 by tpicchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdbool.h>

typedef struct s_philo
{
	int				id;
	int				tot_philo;
	int				tot_meal;
	size_t			last_meal;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			start;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*print_mtx;
}				t_philo;

// main.c
void	*philo_life(void *arg);
int		ft_usleep(size_t time);

// parsing.c
int		ft_check_args(int ac, char **av);
int		ft_check_num(char *str);
int		ft_atoi(const char *str);
void	ft_putnbr(long int num);

// init_data.c
int		ft_init_philo(t_philo *philo, pthread_mutex_t *forks,
			pthread_mutex_t *print_mtx, char **av);
int		ft_init_mutex(pthread_mutex_t **forks, pthread_mutex_t **stat_mut,
			char **av);

// utils.c
int		check_and_print(t_philo *philo, int id, char *msg);
size_t	ft_get_time(void);
void	ft_free_all(pthread_mutex_t *forks, t_philo *philo);

#endif
