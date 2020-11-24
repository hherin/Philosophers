/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heleneherin <heleneherin@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 18:49:19 by heleneherin       #+#    #+#             */
/*   Updated: 2020/11/24 13:35:18 by heleneherin      ###   ########.fr       */
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
	if (!philo_init(&philo, &sdata))
		return (0);
	sdata.time = ms_time();
	pth_create(&philo, &sdata);
	free(philo);
	return (1);
}