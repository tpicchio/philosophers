/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpicchio <tpicchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:56:11 by tpicchio          #+#    #+#             */
/*   Updated: 2024/11/13 18:00:11 by tpicchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_semaphores(t_philo *philo, char **av)
{
	sem_t	*forks;
	sem_t	*print_sem;
	sem_t	*stop_sem;

	sem_unlink("/forks");
	sem_unlink("/print");
	sem_unlink("/stop");
	forks = sem_open("/forks", O_CREAT | O_EXCL, 0644, ft_atoi(av[1]));
	if (forks == SEM_FAILED)
		return (write(2, "Semaphore error\n", 16), 2);
	print_sem = sem_open("/print", O_CREAT | O_EXCL, 0644, 1);
	if (print_sem == SEM_FAILED)
		return (write(2, "Semaphore error\n", 16), 2);
	stop_sem = sem_open("/stop", O_CREAT | O_EXCL, 0644, 1);
	if (stop_sem == SEM_FAILED)
		return (write(2, "Semaphore error\n", 16), 2);
	philo->forks = forks;
	philo->print_sem = print_sem;
	philo->stop_sem = stop_sem;
	return (0);
}

void	init_philo(char **av, t_philo *philo, int i)
{
	size_t	start;

	start = ft_get_time();
	philo->id = i + 1;
	philo->tot_philo = ft_atoi(av[1]);
	philo->time_to_die = ft_atoi(av[2]);
	philo->time_to_eat = ft_atoi(av[3]);
	philo->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		philo->tot_meal = ft_atoi(av[5]);
	else
		philo->tot_meal = -1;
	philo->last_meal = start;
	philo->start = start;
}

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

int	ft_check_args(int ac, char **av)
{
	if (ac < 5 || ac > 6)
		return (write(2, "Invalid number of arguments\n", 28));
	if (ft_check_num(av[1]))
		return (write(2, "Invalid number of philosophers\n", 31));
	if (ft_atoi(av[1]) > 200)
		return (write(2, "Too many philosophers\n", 23));
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
