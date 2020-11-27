/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heleneherin <heleneherin@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 13:05:17 by heleneherin       #+#    #+#             */
/*   Updated: 2020/11/27 11:57:50 by heleneherin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo3.h"

static void	digitcopy(char dest[100], long nb, int index, int nb_len)
{
	if (!nb)
		dest[index] = '0';
	while (nb)
	{
		(dest)[index + nb_len] = nb % 10 + '0';
		nb /= 10;
		nb_len--;
	}
}

static void	stgcopy(char dest[100], const char *str, int index)
{
	int i;

	i = 0;
	while (str[i])
	{
		dest[index + i] = str[i];
		i++;
	}
}

int			print_msg(const char *str, t_start *sdata, t_philo *ph)
{
	long	current_time;
	int		nb_len;
	int		i;
	char	msg[100];

	i = 0;
	while (i < 100)
		msg[i++] = '\0';
	current_time = ms_time() - sdata->time;
	nb_len = nblen(current_time);
	digitcopy(msg, current_time, 0, nb_len - 1);
	stgcopy(msg, "ms\t  ", nb_len);
	nb_len += 4;
	digitcopy(msg, ph->id + 1, nb_len - 1, nblen(ph->id + 1));
	nb_len += nblen(ph->id + 1);
	stgcopy(msg, str, nb_len);
	sem_wait(sdata->print);
	(!ph->stop) ? write(1, msg, ft_strlen(msg)) : 0;
	sem_post(sdata->print);
	return (1);
}

int			print_dead(const char *str, t_start *sdata, t_philo *ph)
{
	long	current_time;
	int		nb_len;
	int		i;
	char	msg[100];

	i = 0;
	while (i < 100)
		msg[i++] = '\0';
	current_time = ms_time() - sdata->time;
	nb_len = nblen(current_time);
	digitcopy(msg, current_time, 0, nb_len - 1);
	stgcopy(msg, "ms\t  ", nb_len);
	nb_len += 4;
	digitcopy(msg, ph->id + 1, nb_len - 1, nblen(ph->id + 1));
	nb_len += nblen(ph->id + 1);
	stgcopy(msg, str, nb_len);
	sem_wait(sdata->print);
	write(1, msg, ft_strlen(msg));
	sem_post(sdata->print);
	return (1);
}

int			p_error(const char *s)
{
	write(2, s, ft_strlen(s));
	write(2, "\n", 1);
	return (0);
}
