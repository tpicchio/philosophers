/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpicchio <tpicchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 16:16:45 by tpicchio          #+#    #+#             */
/*   Updated: 2024/02/20 14:30:50 by tpicchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print(t_philo *philo, int id, char *msg)
{
	size_t	time;

	pthread_mutex_lock(philo->print_lock);
	time = ft_get_time() - philo->birth_time;
	if (!ft_is_alive(philo))
		printf("%zu %d %s\n", time, id, msg);
	pthread_mutex_unlock(philo->print_lock);
}

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
		pthread_mutex_lock(philo[0].perish_lock);
		*philo->perished = 1;
		pthread_mutex_unlock(philo[0].perish_lock);
		return (1);
	}
	return (0);
}

void	*ft_supervisor(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	while (1)
		if (ft_death_check(philo) || ft_check_all_satisfied(philo) == 1)
			break ;
	return (p);
}
