/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heleneherin <heleneherin@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 19:03:20 by heleneherin       #+#    #+#             */
/*   Updated: 2020/11/20 12:03:23 by heleneherin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo1.h"

int	sdata_init(t_start *start, char **av, int ac)
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
	pthread_mutex_init(&start->print, NULL);
	start->dead = 0;
	return (1);
}

void	philo_init(t_philo **philo, t_start *sdata) // ret error
{
	int i;

	i = -1;
	while (++i < sdata->nb_philo)
	{
		(*philo)[i].sdata = sdata;
		(*philo)[i].id = i;
		(*philo)[i].t_save = (void*)(*philo);
		pthread_mutex_init(&((*philo)[i].mutex), NULL);
	}
}

void	pth_create(t_philo **philo, t_start sdata)
{
	int i;

	i = -1;
	while (++i < sdata.nb_philo) // creation des threads
		pthread_create(&(*philo)[i].thrd, NULL, philo_routine, (void*)((*philo) + i));
}

void	pth_join(t_philo **philo, t_start sdata)
{
	int i;

	i = -1;
	while (++i < sdata.nb_philo) // join les threads
		pthread_join((*philo)[i].thrd, NULL);
}