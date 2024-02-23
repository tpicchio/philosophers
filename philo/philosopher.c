/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpicchio <tpicchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:11:16 by tpicchio          #+#    #+#             */
/*   Updated: 2024/02/20 15:37:16 by tpicchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_is_alive(t_philo *philo)
{
	pthread_mutex_lock(philo->perish_lock);
	if (*philo->perished == 1)
	{
		pthread_mutex_unlock(philo->perish_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->perish_lock);
	return (0);
}

static void	*ft_philo_sad_life(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	if (philo->id % 2 == 0)
		ft_my_usleep(1);
	while (!ft_is_alive(philo))
	{
		ft_snack(philo);
		ft_nap(philo);
		ft_think_about_life(philo);
	}
	return (p);
}

int	ft_create_philos(t_monitor *monitor)
{
	pthread_t	supervisor;
	int			i;

	i = 0;
	while (i < monitor->philo[0].tot_philo)
	{
		if (pthread_create(&monitor->philo[i].thread, NULL, &ft_philo_sad_life,
				&monitor->philo[i]) != 0)
			return (write(2, "Error: failed to create a thread\n", 33));
		i++;
	}
	if (pthread_create(&supervisor, NULL, &ft_supervisor, monitor->philo) != 0)
		return (write(2, "Error: failed to create a thread\n", 33));
	i = 0;
	if (pthread_join(supervisor, NULL) != 0)
		return (write(2, "Error: failed to join the threads\n", 34));
	while (i < monitor->philo[0].tot_philo)
	{
		if (pthread_join(monitor->philo[i].thread, NULL) != 0)
			return (write(2, "Error: failed to join the threads\n", 34));
		i++;
	}
	return (0);
}
