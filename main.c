/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heleneherin <heleneherin@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 22:07:45 by heleneherin       #+#    #+#             */
/*   Updated: 2020/11/15 11:53:11 by heleneherin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo1.h"

void	*print_smth(void *smth)
{
	struct timeval tv_philo;

	gettimeofday(&tv_philo, NULL);
	printf("create philosophe %s\n", smth);
	return (smth);
}

int main(int ac, char **av)
{
	pthread_t	*thrd;
	t_start		start;
	int i =    -1;

	if (!struct_fill(&start, av, ac))
		return (0);
	gettimeofday(&tv_init, NULL);
	if (!(thrd = (pthread_t*)malloc(sizeof(pthread_t) * start.nb_philo)))
		return (p_error("Malloc failed"));


	while (++i < start.nb_philo) // creation des threads
		pthread_create(&thrd[i], NULL, print_smth, (void*)ft_itoa(i + 1));
	i = -1;
	while (++i < start.nb_philo) // on attend la fin exec thread avant de quitter ler main
		pthread_join(thrd[i], (void**)ft_itoa(i + 1));
	return (1);
}