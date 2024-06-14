/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpicchio <tpicchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 10:39:25 by tpicchio          #+#    #+#             */
/*   Updated: 2024/06/14 15:44:11 by tpicchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_print(t_philo *philo, int id, char *msg)
{
	size_t			time;

	pthread_mutex_lock(philo->stat_mutex);
	time = ft_get_time() - philo->start;
	if (*(philo->status) != -1 && msg[0] == 'd')
	{
		*(philo->status) = -1;
		printf("%zu %d %s\n", time, id, msg);
		pthread_mutex_unlock(philo->stat_mutex);
		return (0);
	}
	else if (*(philo->status) == -1)
	{
		pthread_mutex_unlock(philo->stat_mutex);
		return (0);
	}
	if (msg[3] == 'e')
	{
		philo->tot_meal--;
		if (philo->tot_meal == 0)
			*(philo->status) = *philo->status + 1;
		if (*(philo->status) == philo->tot_philo)
		{
			pthread_mutex_unlock(philo->stat_mutex);
			return (0);
		}
	}
	printf("%zu %d %s\n", time, id, msg);
	pthread_mutex_unlock(philo->stat_mutex);
	return (1);
}

int	ft_usleep(size_t time)
{
	size_t	start;

	start = ft_get_time();
	while (ft_get_time() - start < time)
		usleep(100);
	return (0);
}

size_t	ft_get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "Error: failed to get time\n", 26);
	return (time.tv_sec * 1000 + time.tv_usec * 0.001);
}

int	ft_atoi(const char *str)
{
	int		i;
	long	nb;

	i = 0;
	nb = 0;
	if (str[i] == '+')
		i++;
	while (str[i])
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	return (nb);
}

void	ft_free_all(pthread_mutex_t *forks, t_philo *philo)
{
	int	i;
	int	tot;

	i = 0;
	tot = philo[0].tot_philo;
	while (i < tot)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	free(philo);
	free(forks);
}
