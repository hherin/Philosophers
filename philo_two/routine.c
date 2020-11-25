/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heleneherin <heleneherin@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 13:50:09 by heleneherin       #+#    #+#             */
/*   Updated: 2020/11/25 15:38:21 by heleneherin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo2.h"


static void	has_eaten_enough(t_philo *ph)
{
	ph->meals++;
	if (ph->meals > 0 && ph->meals == ph->sdata->state[MEALS])
	{
		ph->sdata->counter--;
		sem_wait(ph->sdata->print);
		if (!ph->sdata->counter && !g_stop)
		{
			g_stop = 1;
			write(1, "All has eaten\n", 14);
		}
		sem_post(ph->sdata->print);
	}
}

static void	is_eating(t_philo *ph, t_start *sdata)
{
	sem_wait(sdata->fork);				//take fork 1
	(!g_stop) ? print_msg(" has taken a fork\n", ph->sdata, ph) : 0;
	(!g_stop) ? print_msg(" has taken a fork\n", ph->sdata, ph) : 0;
	(!g_stop) ? print_msg(" is eating\n", ph->sdata, ph) : 0;
	has_eaten_enough(ph);
	ph->time[0] = ms_time();
	better_sleep(ph->sdata->state[EAT] * 1000);
}

static void	is_sleeping(t_philo *ph, t_start *sdata)
{
	sem_post(sdata->fork);
	(!g_stop) ? print_msg(" is sleeping\n", ph->sdata, ph) : 0;
	better_sleep(ph->sdata->state[EAT] * 1000);
}

void	*time_counter(void *philo)
{
	t_philo *ph;
	t_start *data;

	ph = (t_philo*)philo;
	data = ph->sdata;
	ph->time[0] = ms_time();
	while (!g_stop)
	{
		ph->time[1] = ms_time();
		if (ph->time[1] - ph->time[0] > data->state[DIE])
		{
			sem_wait(data->die);
			if (!g_stop && data->counter)
			{
				g_stop = 1;
				usleep(100);
				print_msg(" died\n", data, ph);
			}
			sem_post(data->die);
		}
	}
	return (NULL);
}

void	*philo_routine(void *philo)
{
	t_philo *ph;
	pthread_t th_died;

	ph = (t_philo*)philo;
	while (!ph->sdata->start)
		;
	pthread_create(&th_died, NULL, time_counter, ph);
	while (!g_stop)
	{
		is_eating(ph, ph->sdata);
		is_sleeping(ph, ph->sdata);
		(!g_stop) ? print_msg(" is thinking\n", ph->sdata, ph) : 0;
		usleep(100);
	}
	return (NULL);
}