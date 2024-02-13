/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpicchio <tpicchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 11:55:21 by tpicchio          #+#    #+#             */
/*   Updated: 2024/02/13 10:48:28 by tpicchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_check_num(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (str[i] == 0 && str[i + 1] == 0)
		return (1);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_monitor		monitor;
	t_philo			*philo;
	pthread_mutex_t	*forks;

	if (ac < 5 || ac > 6)
		return (printf("Invalid number of arguments\n"));
	
	return (0);
}
