/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpicchio <tpicchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 10:39:25 by tpicchio          #+#    #+#             */
/*   Updated: 2024/03/21 11:36:33 by tpicchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print(t_philo *philo, int id, char *msg)
{
	size_t	time;

	pthread_mutex_lock(philo->print_lock);
	time = ft_get_time() - philo->birth_time;
	if (!ft_is_alive(philo))
		printf("\033[1;%dm%zu %d %s\033[0m\n", (id % 16) + 31, time, id, msg);
	pthread_mutex_unlock(philo->print_lock);
}

int	ft_my_usleep(size_t time)
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
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
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

void	ft_free_all(t_monitor *monitor, pthread_mutex_t *forks, t_philo *philo)
{
	int	i;
	int	tot;

	i = 0;
	tot = monitor->philo[0].tot_philo;
	pthread_mutex_destroy(&monitor->snack_lock);
	pthread_mutex_destroy(&monitor->print_lock);
	pthread_mutex_destroy(&monitor->perish_lock);
	while (i < tot)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	free(philo);
	free(forks);
}
