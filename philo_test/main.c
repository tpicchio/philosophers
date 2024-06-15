/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpicchio <tpicchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 09:53:14 by tpicchio          #+#    #+#             */
/*   Updated: 2024/06/14 16:38:55 by tpicchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	lock_forks(t_philo *philo, pthread_mutex_t *forks1,
		pthread_mutex_t *forks2)
{
	pthread_mutex_lock(forks1);
	ft_print(philo, philo->id, "has taken a fork");
	pthread_mutex_lock(forks2);
	ft_print(philo, philo->id, "has taken a fork");
}

void	*philo_life(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (ft_print(philo, philo->id, "is thinking") == 0)
			return (NULL);
		if ((ft_get_time() - philo->last_meal) > philo->time_to_die)
			return (ft_print(philo, philo->id, "died"), NULL);
		if (philo->id % 2 == 0)
			lock_forks(philo, philo->right_fork, philo->left_fork);
		else
			lock_forks(philo, philo->left_fork, philo->right_fork);
		ft_print(philo, philo->id, "is eating");
		philo->last_meal = ft_get_time();
		ft_usleep(philo->time_to_eat);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		if (ft_print(philo, philo->id, "is sleeping") == 0)
			return (NULL);
		ft_usleep(philo->time_to_sleep);
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	int				i;
	int				tot_philo;
	t_philo			*philo;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*stat_mutex;

	if (ft_check_args(ac, av))
		return (1);
	philo = malloc(sizeof(t_philo) * ft_atoi(av[1]));
	if (!philo)
		return (write(2, "Malloc error\n", 13), 2);
	forks = NULL;
	stat_mutex = NULL;
	ft_init_mutex(&forks, &stat_mutex, av);
	if (ft_init_philo(philo, forks, stat_mutex, av) == -1)
		return (ft_free_all(forks, philo), 3);
	i = -1;
	tot_philo = ft_atoi(av[1]);
	while (++i < tot_philo)
		pthread_join(philo[i].thread, NULL);
	ft_free_all(forks, philo);
	return (0);
}
