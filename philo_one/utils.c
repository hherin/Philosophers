/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 19:18:42 by heleneherin       #+#    #+#             */
/*   Updated: 2020/11/26 20:46:39 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo1.h"

long				ms_time(void)
{
	long ms;
	struct timeval value;

	ms = 0;
	gettimeofday(&value, NULL);
	ms = value.tv_sec * 1000;
	ms += value.tv_usec / 1000;
	return (ms);
}

void	better_sleep(long d)
{
	struct timeval tmp;
	struct timeval start;

	gettimeofday(&start, NULL);
	while (1)
	{
		usleep(50);
		gettimeofday(&tmp, NULL);
		if ((((long)(tmp.tv_sec - start.tv_sec)) * 1000000 + ((long)(tmp.tv_usec - start.tv_usec))) >= d)
			return ;
	}
}

size_t ft_strlen(const char *str)
{
	int i = 0;
	while (str[i])
		i++;
	return (i);
}

int		ft_atoi(const char *str)
{
	long	nb;
	int		signe;

	nb = 0;
	signe = 1;
	while ((*str < 14 && *str >= 9) || *str == 32)
		str++;
	signe = (*str == '-') ? -1 : 1;
	str = (*str == '-' || *str == '+') ? str + 1 : str;
	while (*str <= (unsigned char)'9' && *str >= (unsigned char)'0')
	{
		nb = nb * 10 + *str - '0';
		str++;
	}
	return (nb * signe);
}

int	nblen(long nb)
{
	int length;

	length = (!nb) ? 1 : 0;
	while (nb)
	{
		nb /= 10;
		length++;
	}
	return (length);
}
