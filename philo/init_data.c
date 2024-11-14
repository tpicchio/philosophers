/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpicchio <tpicchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:23:59 by tpicchio          #+#    #+#             */
/*   Updated: 2024/06/17 10:30:12 by tpicchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_init_mutex(pthread_mutex_t **forks, pthread_mutex_t **stat_mut,
	char **av)
{
	int	i;
	int	tot_philo;

	*forks = malloc(sizeof(pthread_mutex_t) * ft_atoi(av[1]));
	if (!*forks)
		return (write(2, "Malloc error\n", 13), 2);
	i = -1;
	tot_philo = ft_atoi(av[1]);
	while (++i < tot_philo)
		pthread_mutex_init(&(*forks)[i], NULL);
	*stat_mut = malloc(sizeof(pthread_mutex_t));
	if (!*stat_mut)
		return (write(2, "Malloc error\n", 13), 2);
	pthread_mutex_init(*stat_mut, NULL);
	return (0);
}

static void	set_atoi_val(int *atoi_val, char **av)
{
	atoi_val[0] = ft_atoi(av[1]);
	atoi_val[1] = ft_atoi(av[2]);
	atoi_val[2] = ft_atoi(av[3]);
	atoi_val[3] = ft_atoi(av[4]);
	if (av[5])
		atoi_val[4] = ft_atoi(av[5]);
	else
		atoi_val[4] = -1;
}

static void	set_philo_data(t_philo *philo, pthread_mutex_t *forks,
		char **av, int i)
{
	int	atoi_val[5];

	set_atoi_val(atoi_val, av);
	philo[i].id = i + 1;
	philo[i].tot_philo = atoi_val[0];
	philo[i].time_to_die = atoi_val[1];
	philo[i].time_to_eat = atoi_val[2];
	philo[i].time_to_sleep = atoi_val[3];
	philo[i].tot_meal = atoi_val[4];
	philo[i].left_fork = &forks[i];
	if (atoi_val[0] == 1)
		philo[i].right_fork = NULL;
	else
		philo[i].right_fork = &forks[(i + 1) % atoi_val[0]];
}

int	ft_init_philo(t_philo *philo, pthread_mutex_t *forks,
		pthread_mutex_t *print_mtx, char **av)
{
	int		i;
	int		tot_philo;
	size_t	start;

	tot_philo = ft_atoi(av[1]);
	start = ft_get_time();
	i = 0;
	while (i < tot_philo)
	{
		philo[i].print_mtx = print_mtx;
		philo[i].last_meal = start;
		philo[i].start = start;
		set_philo_data(philo, forks, av, i);
		if (pthread_create(&philo[i].thread, NULL, philo_life, &philo[i]) != 0)
			return (write(2, "Thread creation error\n", 23), -1);
		i++;
	}
	return (0);
}
