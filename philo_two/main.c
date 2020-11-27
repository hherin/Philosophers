/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heleneherin <heleneherin@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 13:30:25 by heleneherin       #+#    #+#             */
/*   Updated: 2020/11/27 11:31:36 by heleneherin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo2.h"

int		main(int ac, char **av)
{
	t_start sdata;
	t_philo *philo;

	if (!sdata_init(&sdata, av, ac))
		return (0);
	if (!(philo = (t_philo*)malloc(sizeof(t_philo) * sdata.nb_philo)))
		return (p_error("Malloc failed"));
	philo_init(philo, &sdata);
	if (!pth_create(philo, &sdata))
		return (0);
	if (sem_close(sdata.fork) || sem_close(sdata.print) || sem_close(sdata.die))
		return (p_error("Fail in sem_close"));
	free(philo);
	return (1);
}
