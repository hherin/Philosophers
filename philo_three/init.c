/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 19:03:20 by heleneherin       #+#    #+#             */
/*   Updated: 2020/11/26 21:49:26 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo3.h"

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
	sem_unlink("FORK");
	sem_unlink("PRINT");
	sem_unlink("WAIT");
	sem_unlink("DIE"); ///
	sem_unlink("MEALS");
	if (!str_digit(av[1]) || !(start->nb_philo = ft_atoi(av[1])))
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
	start->fork = sem_open("FORK", O_CREAT, 0644, (unsigned int)start->nb_philo / 2);
	start->print = sem_open("PRINT", O_CREAT, 0644, 1);
	start->die = sem_open("DIE", O_CREAT, 0644, 1);
	start->wait = sem_open("WAIT", O_CREAT, 0644, 0);
	start->meals = sem_open("MEALS", O_CREAT, 0644, 0);
	return (1);
}

void 		philo_init(t_philo *philo, t_start *sdata) // ret error
{
	int i;

	i = -1;
	while (++i < sdata->nb_philo)
	{
		philo[i].sdata = sdata;
		philo[i].id = i;
		philo[i].meals = 0;
		philo[i].stop = 0;
	}
}

int			philo_create(t_philo *philo, t_start *sdata)
{
	int		i;
	int		status;
	pid_t	pid;

	i = -1;
	pid = 1;
	sdata->time = ms_time();
	while (++i < sdata->nb_philo && pid > 0)
	{
		pid = fork();
		if (pid < 0)
			return (p_error("error on fork"));
		else if (!pid)
			status = philo_routine(&philo[i]);
	}
	if (pid > 0)
	{
		i = -1;
		while (++i < sdata->nb_philo)
			sem_post(sdata->wait);
		if (sdata->state[MEALS] > 0)
		{
			pthread_create(&sdata->counter, NULL, meals_counter, sdata);
			pthread_join(sdata->counter, NULL);
		}
		waitpid(-1, &status, 0);
		kill(0, SIGINT);
	}
	return (0);
}
