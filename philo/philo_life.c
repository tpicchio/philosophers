/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpicchio <tpicchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 10:31:00 by tpicchio          #+#    #+#             */
/*   Updated: 2024/02/20 11:28:30 by tpicchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_snack(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	ft_print(philo, philo->id, "has taken a fork");
	if (philo->tot_philo == 1)
	{
		ft_my_usleep(philo->perish_time);
		pthread_mutex_unlock(philo->right_fork);
		return ;
	}
	pthread_mutex_lock(philo->left_fork);
	ft_print(philo, philo->id, "has taken a fork");
	philo->snacking = 1;
	ft_print(philo, philo->id, "is eating");
	pthread_mutex_lock(philo->snack_lock);
	philo->last_snack = ft_get_time();
	philo->snacks_eaten++;
	pthread_mutex_unlock(philo->snack_lock);
	ft_my_usleep(philo->snack_time);
	philo->snacking = 0;
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	ft_nap(t_philo *philo)
{
	ft_print(philo, philo->id, "is sleeping");
	ft_my_usleep(philo->nap_time);
}

void	ft_think_about_life(t_philo *philo)
{
	ft_print(philo, philo->id, "is thinking");
}
