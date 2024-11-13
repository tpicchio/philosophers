/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpicchio <tpicchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 15:00:54 by tpicchio          #+#    #+#             */
/*   Updated: 2024/11/13 18:08:00 by tpicchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <semaphore.h> 
# include <fcntl.h>
# include <sys/time.h>
# include <signal.h>
# include <pthread.h>

typedef struct s_philo
{
	int				id;
	int				tot_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				tot_meal;
	size_t			last_meal;
	size_t			start;
	sem_t			*forks;
	sem_t			*print_sem;
	sem_t			*stop_sem;
}	t_philo;

size_t	ft_get_time(void);
void	init_philo(char **av, t_philo *philo, int i);
void	ft_putnbr(long int num);
int		ft_atoi(const char *str);
int		ft_check_args(int ac, char **av);
int		ft_strlen(char *str);
int		ft_strncmp(char *s1, char *s2, int n);
int		create_semaphores(t_philo *philo, char **av);
int		ft_usleep(size_t time);

#endif
