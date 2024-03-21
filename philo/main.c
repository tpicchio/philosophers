/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpicchio <tpicchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 11:55:21 by tpicchio          #+#    #+#             */
/*   Updated: 2024/03/20 12:38:22 by tpicchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_check_num(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+')
		i++;
	if (str[i] == '0')
		return (1);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

static int	ft_check_args(int ac, char **av)
{
	if (ft_check_num(av[1]))
		return (write(2, "Invalid number of philosophers\n", 31));
	if (ft_check_num(av[2]))
		return (write(2, "Invalid time to die\n", 20));
	if (ft_check_num(av[3]))
		return (write(2, "Invalid time to eat\n", 20));
	if (ft_check_num(av[4]))
		return (write(2, "Invalid time to sleep\n", 22));
	if (ac == 6)
	{
		if (ft_check_num(av[5]))
			return (write(2, "Invalid number of times philosophers must eat\n"
					, 46));
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_monitor		monitor;
	t_philo			*philo;
	pthread_mutex_t	*forks;

	if (ac < 5 || ac > 6)
		return (write(2, "Invalid number of arguments\n", 28));
	if (ft_check_args(ac, av))
		return (1);
	philo = malloc(sizeof(t_philo) * ft_atoi(av[1]));
	if (!philo)
		return (write(2, "Malloc error\n", 13), 1);
	forks = malloc(sizeof(pthread_mutex_t) * ft_atoi(av[1]));
	if (!forks)
		return (write(2, "Malloc error\n", 13), 1);
	ft_setup_monitor(&monitor, philo);
	ft_setup_forks(forks, ft_atoi(av[1]));
	ft_setup_philo(philo, &monitor, forks, av);
	ft_create_philos(&monitor);
	ft_free_all(&monitor, forks, philo);
	return (0);
}
