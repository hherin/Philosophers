/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heleneherin <heleneherin@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 22:34:11 by heleneherin       #+#    #+#             */
/*   Updated: 2020/11/20 10:34:28 by heleneherin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct	s_start
{
	long		time;
	pthread_mutex_t	print;
	int			nb_philo;
	int			die;
	int			eat;
	int			sleep;
	int			nb_meals;
	int			dead;
}				t_start;

typedef struct		s_philo
{
	long			time[2];
	int				id;
	int				state;
	pthread_t		thrd;
	pthread_mutex_t	mutex;
	t_start			*sdata;
	void			*t_save;
}					t_philo;

#endif