/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heleneherin <heleneherin@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 19:02:56 by heleneherin       #+#    #+#             */
/*   Updated: 2020/11/27 12:04:28 by heleneherin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo1.h"

static void	has_eaten_enough(t_philo *ph)
{
	ph->meals++;
	if (ph->meals > 0 && ph->meals == ph->sdata->nb_meals)
	{
		ph->sdata->counter--;
		pthread_mutex_lock(&ph->sdata->stop);
		pthread_mutex_lock(&ph->sdata->print);
		if (!ph->sdata->counter && !g_stop)
		{
			g_stop = 2;
			write(1, "All has eaten\n", 14);
		}
		pthread_mutex_unlock(&ph->sdata->print);
		pthread_mutex_unlock(&ph->sdata->stop);
	}
}

static void	is_eating(t_philo *ph, int id)
{
	int		lock[2];
	t_philo	*ph_tab;

	ph_tab = (t_philo*)(ph->t_save);
	lock[0] = (!(id % 2)) ? id + 1 : id;
	(lock[0] == ph->sdata->nb_philo) ? lock[0] = 0 : 0;
	lock[1] = (!(id % 2)) ? id : id - 1;
	pthread_mutex_lock(&ph_tab[lock[0]].fork);
	print_msg(" has taken a fork\n", ph->sdata, ph);
	pthread_mutex_lock(&ph_tab[lock[1]].fork);
	print_msg(" has taken a fork\n", ph->sdata, ph);
	print_msg(" is eating\n", ph->sdata, ph);
	has_eaten_enough(ph);
	ph->time[0] = ms_time();
	better_sleep(ph->sdata->eat * 1000);
}

static void	is_sleeping(t_philo *ph, int id)
{
	int		unlock[2];
	t_philo	*ph_tab;

	ph_tab = (t_philo*)(ph->t_save);
	unlock[0] = (!(id % 2)) ? id + 1 : id;
	(unlock[0] == ph->sdata->nb_philo) ? unlock[0] = 0 : 0;
	unlock[1] = (!(id % 2)) ? id : id - 1;
	pthread_mutex_unlock(&ph_tab[unlock[0]].fork);
	pthread_mutex_unlock(&ph_tab[unlock[1]].fork);
	print_msg(" is sleeping\n", ph->sdata, ph);
	better_sleep(ph->sdata->eat * 1000);
}

void		*time_counter(void *philo)
{
	t_philo *ph;
	t_start *data;

	ph = (t_philo*)philo;
	data = ph->sdata;
	ph->time[0] = ms_time();
	while (!g_stop)
	{
		ph->time[1] = ms_time();
		if (ph->time[1] - ph->time[0] >= data->die)
		{
			pthread_mutex_lock(&data->stop);
			if (!g_stop && data->counter)
			{
				g_stop = 1;
				usleep(100);
				print_dead(" died\n", data, ph);
			}
			pthread_mutex_unlock(&data->stop);
		}
	}
	return (NULL);
}

void		*philo_routine(void *philo)
{
	t_philo		*ph;
	pthread_t	th_died;

	ph = (t_philo*)philo;
	while (!ph->sdata->start)
		;
	pthread_create(&th_died, NULL, time_counter, ph);
	while (!g_stop)
	{
		is_eating(ph, ph->id);
		is_sleeping(ph, ph->id);
		print_msg(" is thinking\n", ph->sdata, ph);
		usleep(100);
	}
	return (NULL);
}
