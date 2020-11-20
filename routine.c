/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heleneherin <heleneherin@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 19:02:56 by heleneherin       #+#    #+#             */
/*   Updated: 2020/11/20 14:15:52 by heleneherin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo1.h"

void	*compt(void *ph)
{
	t_philo *philo;

	philo = (t_philo*)ph;
	while (!philo->sdata->dead)
	{
		philo->time[1] = ms_time();
		if (philo->time[1] - philo->time[0] > philo->sdata->die)
		{
			pthread_mutex_lock(&philo->sdata->print);
			if (!philo->sdata->dead)
				printf("%ldms\t- %d\tis dead\n", philo->time[1] - philo->sdata->time, philo->id + 1);
			philo->sdata->dead = 1;
			pthread_mutex_unlock(&philo->sdata->print);
		}
	}
	return (NULL);
}

void	*philo_routine(void *ph)
{
	t_philo *philo;
	pthread_t th_died;

	philo = (t_philo*)ph;
	philo->time[0] = ms_time();
	pthread_create(&th_died, NULL, compt, ph);
	while (!philo->sdata->dead)
	{
		is_eating(&philo, philo->id);
		is_sleeping(&philo, philo->id);
	}
	return (NULL);
}