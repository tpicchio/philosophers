/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpicchio <tpicchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 11:36:53 by tpicchio          #+#    #+#             */
/*   Updated: 2024/02/20 10:17:58 by tpicchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_setup_monitor(t_monitor *monitor, t_philo *philo)
{
	monitor->perished = 0;
	monitor->philo = philo;
	pthread_mutex_init(&monitor->snack_lock, NULL);
	pthread_mutex_init(&monitor->print_lock, NULL);
	pthread_mutex_init(&monitor->perish_lock, NULL);
}

void	ft_setup_forks(pthread_mutex_t *forks, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

static void	ft_set_input(t_philo *philo, char **av)
{
	philo->tot_philo = ft_atoi(av[1]);
	philo->perish_time = ft_atoi(av[2]);
	philo->snack_time = ft_atoi(av[3]);
	philo->nap_time = ft_atoi(av[4]);
	if (av[5])
		philo->max_snacks = ft_atoi(av[5]);
	else
		philo->max_snacks = -1;
}

void	ft_setup_philo(t_philo *philo, t_monitor *monitor,
		pthread_mutex_t *forks, char **av)
{
	int	i;

	i = 0;
	while (i < ft_atoi(av[1]))
	{
		philo[i].id = i + 1;
		philo[i].snacking = 0;
		philo[i].snacks_eaten = 0;
		philo[i].last_snack = ft_get_time();
		philo[i].birth_time = ft_get_time();
		philo[i].print_lock = &monitor->print_lock;
		philo[i].snack_lock = &monitor->snack_lock;
		philo[i].perish_lock = &monitor->perish_lock;
		philo[i].perished = &monitor->perished;
		philo[i].left_fork = &forks[i];
		ft_set_input(&philo[i], av);
		if (i == 0)
			philo[i].right_fork = &forks[philo[i].tot_philo - 1];
		else
			philo[i].right_fork = &forks[i - 1];
		i++;
	}
}
