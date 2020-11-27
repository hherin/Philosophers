/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heleneherin <heleneherin@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 19:03:20 by heleneherin       #+#    #+#             */
/*   Updated: 2020/11/27 11:03:08 by heleneherin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo1.h"

extern int	g_stop;

static int	str_digit(const char *str)
{
	while (*str)
	{
		if (*str > (unsigned char)'9' && *str < (unsigned char)'0')
			return (0);
		str++;
	}
	return (1);
}

int			sdata_init(t_start *start, char **av, int ac)
{
	if (ac < 5)
		return (p_error("Need arguments"));
	if (!str_digit(av[1]) || !(start->nb_philo = ft_atoi(av[1])))
		return (p_error("Wrong philosopher input"));
	if (!str_digit(av[2]) || !(start->die = ft_atoi(av[2])))
		return (p_error("Wrong died input"));
	if (!str_digit(av[3]) || !(start->eat = ft_atoi(av[3])))
		return (p_error("Wrong eat input"));
	if (!str_digit(av[4]) || !(start->sleep = ft_atoi(av[4])))
		return (p_error("Wrong eat input"));
	start->nb_meals = (ac > 5) ? ft_atoi(av[5]) : -1;
	if (!start->nb_meals)
		return (p_error("Number of meals can't be negative"));
	if (pthread_mutex_init(&start->print, NULL))
		return (p_error("Mutex init failed"));
	if (pthread_mutex_init(&start->stop, NULL))
		return (p_error("Mutex init failed"));
	start->counter = start->nb_philo;
	return (1);
}

int			philo_init(t_philo **philo, t_start *sdata)
{
	int i;

	i = -1;
	while (++i < sdata->nb_philo)
	{
		(*philo)[i].sdata = sdata;
		(*philo)[i].id = i;
		(*philo)[i].t_save = (void*)(*philo);
		(*philo)[i].meals = 0;
		if (pthread_mutex_init(&((*philo)[i].fork), NULL))
			return (p_error("Fork mutex initialisation failed"));
		if (pthread_mutex_init(&((*philo)[i].pick), NULL))
			return (p_error("Fork mutex initialisation failed"));
	}
	return (1);
}

int			pth_create(t_philo **philo, t_start *sdata)
{
	int i;

	i = -1;
	sdata->start = 0;
	while (++i < sdata->nb_philo)
	{
		if (pthread_create(&(*philo)[i].thrd, NULL, philo_routine, \
			(void*)((*philo) + i)))
			return (p_error("Thread creation failed"));
	}
	sdata->time = ms_time();
	sdata->start = 1;
	i = -1;
	while (++i < sdata->nb_philo)
	{
		if (pthread_join((*philo)[i].thrd, NULL))
			return (p_error("Fail in joining threads"));
	}
	return (1);
}
