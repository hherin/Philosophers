/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heleneherin <heleneherin@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 13:50:09 by heleneherin       #+#    #+#             */
/*   Updated: 2020/11/27 11:51:46 by heleneherin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo3.h"

void		*meals_counter(void *args)
{
	t_start *sdata;
	int		i;

	sdata = (t_start*)args;
	i = 0;
	while (i++ < sdata->nb_philo)
		sem_wait(sdata->meals);
	sem_wait(sdata->print);
	write(1, "All philosophers has eaten enought\n", 34);
	kill(0, SIGINT);
	return (NULL);
}

static void	is_eating(t_philo *ph, t_start *sdata)
{
	sem_wait(sdata->fork);
	print_msg(" has taken a fork\n", ph->sdata, ph);
	print_msg(" has taken a fork\n", ph->sdata, ph);
	print_msg(" is eating\n", ph->sdata, ph);
	ph->meals++;
	if (ph->meals > 0 && ph->meals == ph->sdata->state[MEALS])
		sem_post(ph->sdata->meals);
	ph->time[0] = ms_time();
	better_sleep(ph->sdata->state[EAT] * 1000);
}

static void	is_sleeping(t_philo *ph, t_start *sdata)
{
	sem_post(sdata->fork);
	print_msg(" is sleeping\n", ph->sdata, ph);
	better_sleep(ph->sdata->state[EAT] * 1000);
}

static void	*time_counter(void *philo)
{
	t_philo **ph;
	t_start *data;

	ph = (t_philo**)philo;
	data = (*ph)->sdata;
	(*ph)->time[0] = ms_time();
	while (!(*ph)->stop)
	{
		(*ph)->time[1] = ms_time();
		if ((*ph)->time[1] - (*ph)->time[0] > data->state[DIE])
		{
			sem_wait(data->die);
			if (!(*ph)->stop)
			{
				(*ph)->stop = 1;
				usleep(100);
				print_dead(" died", data, (*ph));
				kill(0, SIGINT);
			}
		}
	}
	return (NULL);
}

int			philo_routine(t_philo *ph)
{
	pthread_t th_died;

	sem_wait(ph->sdata->wait);
	ph->sdata->time = ms_time();
	if (pthread_create(&th_died, NULL, time_counter, &ph))
		return (p_error("Thread creation failed"));
	while (!ph->stop)
	{
		is_eating(ph, ph->sdata);
		is_sleeping(ph, ph->sdata);
		print_msg(" is thinking\n", ph->sdata, ph);
		usleep(100);
	}
	return (ph->stop);
}
