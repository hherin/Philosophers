/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heleneherin <heleneherin@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 18:49:19 by heleneherin       #+#    #+#             */
/*   Updated: 2020/11/27 11:05:04 by heleneherin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo1.h"

int	main(int ac, char **av)
{
	t_start	sdata;
	t_philo	*philo;
	int		i;

	i = -1;
	if (!sdata_init(&sdata, av, ac))
		return (0);
	if (!(philo = (t_philo*)malloc(sizeof(t_philo) * sdata.nb_philo)))
		return (p_error("Malloc failed"));
	if (!philo_init(&philo, &sdata))
		return (0);
	sdata.time = ms_time();
	if (!pth_create(&philo, &sdata))
		return (0);
	while (++i < sdata.nb_philo)
	{
		if (pthread_mutex_destroy(&philo[i].fork) ||
			pthread_mutex_destroy(&philo[i].pick))
			return (p_error("Mutex destroy failed"));
	}
	if (pthread_mutex_destroy(&sdata.print) ||
		pthread_mutex_destroy(&sdata.stop))
		return (p_error("Mutex destroy failed"));
	free(philo);
	return (1);
}
