/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heleneherin <heleneherin@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 13:30:25 by heleneherin       #+#    #+#             */
/*   Updated: 2020/11/26 20:01:06 by heleneherin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo3.h"

int		main(int ac, char **av)
{
	t_start sdata;
	t_philo *philo;
	// pthread_t meals;

	if (!sdata_init(&sdata, av, ac))
		return (0);
	if (!(philo = (t_philo*)malloc(sizeof(t_philo) * sdata.nb_philo)))
		return (p_error("Malloc failed"));
	philo_init(philo, &sdata);
	philo_create(philo, &sdata);
	// if (sdata.state[MEALS] > 0)
	// {
	// 	pthread_create(&meals, NULL, meals_counter, &sdata);
	// 	pthread_join(meals, NULL);
	// }
	return (1);
}