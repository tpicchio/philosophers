/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpicchio <tpicchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 11:55:21 by tpicchio          #+#    #+#             */
/*   Updated: 2024/03/22 09:52:41 by tpicchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_monitor		monitor;
	t_philo			*philo;
	pthread_mutex_t	*forks;
	int				ret;

	if (ac < 5 || ac > 6)
		return (write(2, "Invalid number of arguments\n", 28), -1);
	if (ft_check_args(ac, av))
		return (-1);
	philo = malloc(sizeof(t_philo) * ft_atoi(av[1]));
	if (!philo)
		return (write(2, "Malloc error\n", 13), -1);
	forks = malloc(sizeof(pthread_mutex_t) * ft_atoi(av[1]));
	if (!forks)
		return (write(2, "Malloc error\n", 13), -1);
	ft_setup_mutexes(&monitor, philo, forks, ft_atoi(av[1]));
	ft_setup_philo(philo, &monitor, forks, av);
	ret = ft_create_philos(&monitor);
	ft_free_all(&monitor, forks, philo);
	return (ret);
}
