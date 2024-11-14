/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpicchio <tpicchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 12:02:27 by tpicchio          #+#    #+#             */
/*   Updated: 2024/11/14 11:45:14 by tpicchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_putnbr(long int num)
{
	long int	cifre;
	long int	tmp;
	char		c;

	cifre = 1;
	tmp = num;
	if (num == 0)
		cifre = 10;
	while (tmp > 0)
	{
		tmp = tmp / 10;
		cifre *= 10;
	}
	while (cifre > 1)
	{
		c = (num / (cifre / 10)) + '0';
		num = num % (cifre / 10);
		cifre /= 10;
		write(1, &c, 1);
	}
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

int	ft_check_num(char *str)
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
