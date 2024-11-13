/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpicchio <tpicchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 18:00:22 by tpicchio          #+#    #+#             */
/*   Updated: 2024/11/13 18:00:26 by tpicchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	clean_exit(t_philo philo, int taken_forks)
{
	int	i;

	i = 0;
	while (i++ < taken_forks)
		sem_post(philo.forks);
	sem_close(philo.forks);
	sem_close(philo.print_sem);
	sem_close(philo.stop_sem);
	exit(0);
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

static void	check_and_print(t_philo philo, char *msg, int taken_forks)
{
	size_t	time;
	int		val;
	int		i;

	sem_wait(philo.print_sem);
	time = ft_get_time();
	sem_getvalue(philo.stop_sem, &val);
	i = 0;
	if (val < 1 || philo.tot_meal == 0)
	{
		sem_post(philo.print_sem);
		clean_exit(philo, taken_forks);
	}
	if ((int)(time - philo.last_meal) > philo.time_to_die)
	{
		sem_wait(philo.stop_sem);
		ft_print(time - philo.start, philo.id, "died");
		sem_post(philo.print_sem);
		clean_exit(philo, taken_forks);
	}
	ft_print(time - philo.start, philo.id, msg);
	sem_post(philo.print_sem);
}

void	philo_life(t_philo philo)
{
	size_t	time;

	while (1)
	{
		check_and_print(philo, "is thinking", 0);
		sem_wait(philo.forks);
		check_and_print(philo, "has taken a fork", 1);
		sem_wait(philo.forks);
		time = ft_get_time();
		philo.last_meal = time;
		check_and_print(philo, "has taken a fork", 2);
		check_and_print(philo, "is eating", 2);
		if (philo.tot_meal != -1)
			philo.tot_meal--;
		ft_usleep(philo.time_to_eat);
		sem_post(philo.forks);
		sem_post(philo.forks);
		check_and_print(philo, "is sleeping", 0);
		ft_usleep(philo.time_to_sleep);
	}
}

int	main(int ac, char **av)
{
	t_philo			philo;
	int				i;

	if (ft_check_args(ac, av))
		return (1);
	if (create_semaphores(&philo, av) == 2)
		return (1);
	i = 0;
	while (i < ft_atoi(av[1]))
	{
		init_philo(av, &philo, i);
		if (fork() == 0)
			philo_life(philo);
		i++;
	}
	i = 0;
	while (i++ < ft_atoi(av[1]))
		wait(NULL);
	sem_close(philo.forks);
	sem_close(philo.print_sem);
	sem_close(philo.stop_sem);
	sem_unlink("/forks");
	sem_unlink("/print");
	sem_unlink("/stop");
	return (0);
}
