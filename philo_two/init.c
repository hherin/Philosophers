/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heleneherin <heleneherin@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 19:03:20 by heleneherin       #+#    #+#             */
/*   Updated: 2020/11/28 12:32:54 by heleneherin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo2.h"

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

static int	sem_create(t_start *start)
{
	sem_unlink("FORK");
	sem_unlink("PRINT");
	sem_unlink("DIE");
	start->fork = sem_open("FORK", O_CREAT, 0644,\
		(unsigned int)start->nb_philo / 2);
	start->print = sem_open("PRINT", O_CREAT, 0644, 1);
	start->die = sem_open("DIE", O_CREAT, 0644, 1);
	if (start->fork == SEM_FAILED || start->print == SEM_FAILED ||
		start->die == SEM_FAILED)
		return (p_error("Sem_open failed"));
	return (1);
}

int			sdata_init(t_start *start, char **av, int ac)
{
	if (ac < 5)
		return (p_error("Need arguments"));
	if (!str_digit(av[1]) || !(start->nb_philo = ft_atoi(av[1])) ||
		start->nb_philo > 200)
		return (p_error("Wrong philosopher input"));
	if (!str_digit(av[2]) || !(start->state[DIE] = ft_atoi(av[2])))
		return (p_error("Wrong died input"));
	if (!str_digit(av[3]) || !(start->state[EAT] = ft_atoi(av[3])))
		return (p_error("Wrong eat input"));
	if (!str_digit(av[4]) || !(start->state[SLEEP] = ft_atoi(av[4])))
		return (p_error("Wrong eat input"));
	start->state[MEALS] = (ac > 5) ? ft_atoi(av[5]) : -1;
	if (!start->state[MEALS])
		return (p_error("Number of meals can't be negative"));
	start->counter = start->nb_philo;
	if (!sem_create(start))
		return (0);
	return (1);
}

void		philo_init(t_philo *philo, t_start *sdata)
{
	int i;

	i = -1;
	while (++i < sdata->nb_philo)
	{
		philo[i].sdata = sdata;
		philo[i].id = i;
		philo[i].meals = 0;
	}
}

int			pth_create(t_philo *philo, t_start *sdata)
{
	int i;

	i = -1;
	sdata->start = 0;
	while (++i < sdata->nb_philo)
	{
		if (pthread_create(&philo[i].thrd, NULL, philo_routine,
			(void*)(philo + i)))
			return (p_error("Thread creation failed"));
	}
	sdata->time = ms_time();
	sdata->start = 1;
	i = -1;
	while (++i < sdata->nb_philo)
	{
		if (pthread_join(philo[i].thrd, NULL))
			return (p_error("Thread join failed"));
	}
	return (1);
}
