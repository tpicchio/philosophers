/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpicchio <tpicchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 16:16:45 by tpicchio          #+#    #+#             */
/*   Updated: 2024/03/21 11:55:52 by tpicchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_is_dead(t_philo *philo, size_t perish_time)
{
	pthread_mutex_lock(philo->snack_lock);
	if (ft_get_time() - philo->last_snack >= perish_time
		&& philo->snacking == 0)
	{
		pthread_mutex_unlock(philo->snack_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->snack_lock);
	return (0);
}

static int	ft_death_check(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo[0].tot_philo)
	{
		if (ft_is_dead(&philo[i], philo[i].perish_time))
		{
			ft_print(&philo[i], philo[i].id, "died");
			pthread_mutex_lock(philo[i].perish_lock);
			*philo->perished = 1;
			pthread_mutex_unlock(philo[i].perish_lock);
			return (1);
		}
		i++;
	}
	return (0);
}

static void	ft_set_all_dead(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo[0].tot_philo)
	{
		pthread_mutex_lock(philo[i].perish_lock);
		*philo[i].perished = 1;
		pthread_mutex_unlock(philo[i].perish_lock);
		i++;
	}
}

static int	ft_check_all_satisfied(t_philo *philo)
{
	int	i;
	int	satisfied;

	i = 0;
	satisfied = 0;
	if (philo[0].max_snacks == -1)
		return (0);
	while (i < philo[0].tot_philo)
	{
		pthread_mutex_lock(philo[i].snack_lock);
		if (philo[i].snacks_eaten >= philo[i].max_snacks)
			satisfied++;
		pthread_mutex_unlock(philo[i].snack_lock);
		i++;
	}
	if (satisfied == philo[0].tot_philo)
	{
		ft_set_all_dead(philo);
		return (1);
	}
	return (0);
}

void	*ft_supervisor(void *p)
{
	while (1)
	{
		usleep(1);
		if (ft_death_check((t_philo *)p)
			|| ft_check_all_satisfied((t_philo *)p))
			break ;
	}
	return (p);
}
