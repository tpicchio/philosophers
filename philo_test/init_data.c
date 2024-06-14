/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpicchio <tpicchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:23:59 by tpicchio          #+#    #+#             */
/*   Updated: 2024/06/14 16:40:47 by tpicchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_init_philo(t_philo *philo, pthread_mutex_t *forks, char **av)
{
	int				i;
	int				atoi_val[5];
	int				*status;
	size_t			start;
	pthread_mutex_t	*stat_mutex;

	i = 0;
	atoi_val[0] = ft_atoi(av[1]);
	atoi_val[1] = ft_atoi(av[2]);
	atoi_val[2] = ft_atoi(av[3]);
	atoi_val[3] = ft_atoi(av[4]);
	if (av[5])
		atoi_val[4] = ft_atoi(av[5]);
	else
		atoi_val[4] = -1;
	status = ft_calloc(1, sizeof(int));
	stat_mutex = ft_calloc(1, sizeof(pthread_mutex_t));
	start = ft_get_time();
	while (i < atoi_val[0])
	{
		philo[i].id = i + 1;
		philo[i].tot_philo = atoi_val[0];
		philo[i].time_to_die = atoi_val[1];
		philo[i].time_to_eat = atoi_val[2];
		philo[i].time_to_sleep = atoi_val[3];
		philo[i].last_meal = ft_get_time();
		philo[i].tot_meal = atoi_val[4];
		philo[i].status = status;
		philo[i].start = start;
		philo[i].left_fork = &forks[i];
		philo[i].right_fork = &forks[(i + 1) % atoi_val[0]];
		philo[i].stat_mutex = stat_mutex;
		if (pthread_create(&philo[i].thread, NULL, philo_life, &philo[i]) != 0)
			return (write(2, "Thread creation error\n", 23), -1);
		i++;
	}
	return (0);
}
