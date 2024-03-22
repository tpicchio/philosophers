/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpicchio <tpicchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 10:31:00 by tpicchio          #+#    #+#             */
/*   Updated: 2024/03/21 11:39:04 by tpicchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_think_about_life(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	if (philo->tot_philo == 1)
	{
		pthread_mutex_lock(philo->right_fork);
		ft_print(philo, philo->id, "has taken a fork");
		ft_my_usleep(philo->perish_time);
		pthread_mutex_unlock(philo->right_fork);
		return (p);
	}
	if (ft_is_alive(philo))
		return (p);
	else
	{
		ft_print(philo, philo->id, "is thinking");
		ft_snack(philo);
	}
	return (p);
}

void	ft_snack(t_philo *philo)
{
	if (ft_is_alive(philo))
		return ;
	pthread_mutex_lock(philo->right_fork);
	ft_print(philo, philo->id, "has taken a fork");
	pthread_mutex_lock(philo->left_fork);
	ft_print(philo, philo->id, "has taken a fork");
	pthread_mutex_lock(philo->snack_lock);
	philo->snacking = 1;
	ft_print(philo, philo->id, "is eating");
	philo->snacks_eaten++;
	philo->snacking = 0;
	philo->last_snack = ft_get_time();
	pthread_mutex_unlock(philo->snack_lock);
	ft_my_usleep(philo->snack_time);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	ft_nap(philo);
}

void	ft_nap(t_philo *philo)
{
	if (ft_is_alive(philo))
		return ;
	ft_print(philo, philo->id, "is sleeping");
	ft_my_usleep(philo->nap_time);
	ft_think_about_life(philo);
}

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
