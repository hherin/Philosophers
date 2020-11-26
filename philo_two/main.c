/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 13:30:25 by heleneherin       #+#    #+#             */
/*   Updated: 2020/11/26 21:02:00 by user42           ###   ########.fr       */
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
	pth_create(philo, &sdata);
	free(philo);
	return (1);
}