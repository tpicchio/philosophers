/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpicchio <tpicchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 15:05:15 by tpicchio          #+#    #+#             */
/*   Updated: 2024/11/13 18:00:41 by tpicchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_strncmp(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && i < n)
	{
		if (s1[i] != s2[i])
			return (1);
		i++;
	}
	if (i == n)
		return (0);
	return (1);
}

size_t	ft_get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "Error: failed to get time\n", 26);
	return (time.tv_sec * 1000 + time.tv_usec * 0.001);
}

int	ft_usleep(size_t time)
{
	size_t	start;

	start = ft_get_time();
	while (ft_get_time() - start < time)
		usleep(400);
	return (0);
}

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
