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

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	i;

	ptr = malloc(count * size);
	if (!ptr)
	{
		write(2, "Error: failed to allocate memory\n", 33);
		exit(1);
	}
	i = 0;
	while (i < count * size)
	{
		((char *)ptr)[i] = 0;
		i++;
	}
	return (ptr);
}

// Funzione eseguita dai thread dei filosofi
void *philo_life(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (ft_print(philo, philo->id, "is thinking") == 0)
			return (NULL);
		if (philo->id % 2 == 0)
		{
			pthread_mutex_lock(philo->right_fork);
			if (ft_print(philo, philo->id, "has taken a fork") == 0)
				return (NULL);
			pthread_mutex_lock(philo->left_fork);
			if (ft_print(philo, philo->id, "has taken a fork") == 0)
				return (NULL);
		}
		else
		{
			pthread_mutex_lock(philo->left_fork);
			if (ft_print(philo, philo->id, "has taken a fork") == 0)
				return (NULL);
			pthread_mutex_lock(philo->right_fork);
			if (ft_print(philo, philo->id, "has taken a fork") == 0)
				return (NULL);
		}
		philo->last_meal = ft_get_time();
		if ((ft_get_time() - philo->last_meal) > philo->time_to_die)
		{
			ft_print(philo, philo->id, "died");
			return (NULL);
		}
		if (ft_print(philo, philo->id, "is eating") == 0)
			return (NULL);
		ft_usleep(philo->time_to_eat);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		if (ft_print(philo, philo->id, "is sleeping") == 0)
			return (NULL);
		ft_usleep(philo->time_to_sleep);
	}
	return NULL;
}

int main(int ac, char **av)
{
	int				i;
	t_philo			*philo;
	pthread_mutex_t	*forks;
	
	if (ft_check_args(ac, av))
		return (-1);
	philo = malloc(sizeof(t_philo) * ft_atoi(av[1]));
	if (!philo)
		return (write(2, "Malloc error\n", 13), -1);
	forks = malloc(sizeof(pthread_mutex_t) * ft_atoi(av[1]));
	if (!forks)
		return (write(2, "Malloc error\n", 13), -1);
	i = ft_atoi(av[1]);
	while (--i)
		pthread_mutex_init(&forks[i], NULL);
	if (ft_init_philo(philo, forks, av) == -1)
		return (ft_free_all(forks, philo), -1);
    i = ft_atoi(av[1]);
	while (--i)
		pthread_join(philo[i].thread, NULL);
	ft_free_all(forks, philo);
    return (0);
}
