/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpicchio <tpicchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 10:39:25 by tpicchio          #+#    #+#             */
/*   Updated: 2024/11/14 11:44:07 by tpicchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

static void	ft_print(size_t time, int id, char *msg)
{
	ft_putnbr(time);
	write(1, " ", 1);
	ft_putnbr(id);
	write(1, " ", 1);
	write(1, msg, ft_strlen(msg));
	write(1, "\n", 1);
}

int	check_and_print(t_philo *philo, int id, char *msg)
{
	static int		sts = 0;
	size_t			time;

	time = ft_get_time();
	pthread_mutex_lock(philo->print_mtx);
	if ((time - philo->last_meal) > philo->time_to_die && sts != -1)
	{
		sts = -1;
		ft_print(time - philo->start, id, "died");
		pthread_mutex_unlock(philo->print_mtx);
		return (0);
	}
	else if (sts == -1 || sts == philo->tot_philo)
		return (pthread_mutex_unlock(philo->print_mtx), 0);
	ft_print(time - philo->start, id, msg);
	if (msg[3] == 'e')
	{
		philo->tot_meal--;
		if (philo->tot_meal == 0 && sts != -1)
			sts++;
	}
	pthread_mutex_unlock(philo->print_mtx);
	return (1);
}

size_t	ft_get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "Error: failed to get time\n", 26);
	return (time.tv_sec * 1000 + time.tv_usec * 0.001);
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
	pthread_mutex_destroy(philo[0].print_mtx);
	free(philo[0].print_mtx);
	free(philo);
	free(forks);
}
