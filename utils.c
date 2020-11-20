/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heleneherin <heleneherin@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 19:18:42 by heleneherin       #+#    #+#             */
/*   Updated: 2020/11/20 09:45:43 by heleneherin      ###   ########.fr       */
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

int p_error(const char *s)
{
	int i;

	i = -1;
	while (s[++i])
		write(2, &s[i], 1);
	write(2, "\n", 1);
	return (0);
}

int		str_digit(const char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
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

static int		ft_nblen(unsigned int nb)
{
	int len;

	len = 0;
	if (nb >= 0 && nb < 10)
		return (1);
	while (nb > 0)
	{
		nb /= 10;
		len++;
	}
	return (len);
}

int		ft_isdigit(int c)
{
	if (c <= (unsigned char)'9' && c >= (unsigned char)'0')
		return (1);
	return (0);
}

size_t	ft_strlen(const char *s)
{
	size_t i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char			*ft_itoa(int n)
{
	int				len;
	char			*str;
	unsigned int	nb;

	len = (n < 0) ? ft_nblen(-n) + 1 : ft_nblen(n);
	if (!(str = (char*)malloc(sizeof(char) * len + 1)))
		return (NULL);
	nb = n;
	if (n < 0)
	{
		*str = '-';
		nb = -n;
	}
	*(str + len--) = '\0';
	while (len > (*str == '-' ? 0 : -1))
	{
		if (nb > 9)
		{
			str[len--] = (nb % 10) + '0';
			nb /= 10;
		}
		else
			str[len--] = nb + '0';
	}
	return (str);
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
	while (ft_isdigit(*str))
	{
		nb = nb * 10 + *str - '0';
		str++;
	}
	return (nb * signe);
}

char	*ft_strdup(const char *s1)
{
	char	*str;
	int		i;

	i = 0;
	if (!(str = (char*)malloc(sizeof(char) * ft_strlen(s1) + 1)))
		return (NULL);
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}