/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpicchio <tpicchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 09:53:14 by tpicchio          #+#    #+#             */
/*   Updated: 2024/11/14 11:43:47 by tpicchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_usleep(size_t time)
{
	size_t	start;
	size_t	current;
	size_t	elapsed;

	start = ft_get_time();
	elapsed = ft_get_time() - start;
	while (elapsed < time)
	{
		current = time - elapsed;
		if (current > 10)
			usleep(1000);
		else
			usleep(100);
	}
	return (0);
}

static void	lock_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		check_and_print(philo, philo->id, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		check_and_print(philo, philo->id, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		check_and_print(philo, philo->id, "has taken a fork");
		if (philo->tot_philo == 1)
		{
			ft_usleep(philo->time_to_die + 1);
			return ;
		}
		pthread_mutex_lock(philo->right_fork);
		check_and_print(philo, philo->id, "has taken a fork");
	}
}

static void	ft_unlock_forks(t_philo *philo)
{
	if (philo->right_fork)
		pthread_mutex_unlock(philo->right_fork);
	if (philo->left_fork)
		pthread_mutex_unlock(philo->left_fork);
}

void	*philo_life(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (check_and_print(philo, philo->id, "is thinking") == 0)
			return (NULL);
		if (((philo->id == philo->tot_philo && philo->tot_philo != 2)
				|| philo->id == 1) && philo->tot_philo != 1)
			lock_forks(philo);
		else
			lock_forks(philo);
		if (check_and_print(philo, philo->id, "is eating") == 0)
			return (ft_unlock_forks(philo), NULL);
		ft_usleep(philo->time_to_eat);
		philo->last_meal = ft_get_time();
		ft_unlock_forks(philo);
		if (check_and_print(philo, philo->id, "is sleeping") == 0)
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
	pthread_mutex_t	*print_mtx;

	if (ft_check_args(ac, av))
		return (1);
	philo = malloc(sizeof(t_philo) * ft_atoi(av[1]));
	if (!philo)
		return (write(2, "Malloc error\n", 13), 2);
	forks = NULL;
	print_mtx = NULL;
	ft_init_mutex(&forks, &print_mtx, av);
	if (ft_init_philo(philo, forks, print_mtx, av) == -1)
		return (ft_free_all(forks, philo), 3);
	i = -1;
	tot_philo = ft_atoi(av[1]);
	while (++i < tot_philo)
		pthread_join(philo[i].thread, NULL);
	ft_free_all(forks, philo);
	return (0);
}
