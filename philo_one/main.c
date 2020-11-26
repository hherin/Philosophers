/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heleneherin <heleneherin@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 18:49:19 by heleneherin       #+#    #+#             */
/*   Updated: 2020/11/26 20:12:00 by heleneherin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo1.h"


// checker leaks + protection au max
int main(int ac, char **av)
{
	t_start sdata;
	t_philo *philo;

	if (!sdata_init(&sdata, av, ac))
		return (0);
	if (!(philo = (t_philo*)malloc(sizeof(t_philo) * sdata.nb_philo)))
		return (p_error("Malloc failed"));
	philo_init(&philo, &sdata);
	sdata.time = ms_time();
	pth_create(&philo, &sdata);
	free(philo);
	return (1);
}