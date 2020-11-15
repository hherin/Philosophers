/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heleneherin <heleneherin@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 22:34:11 by heleneherin       #+#    #+#             */
/*   Updated: 2020/11/15 12:04:46 by heleneherin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct	s_start
{
	int			nb_philo;
	int			die;
	int			eat;
	int			sleep;
	int			nb_meals;
}				t_start;

typedef struct		s_philo
{
	int				id;
	int				state;
	pthread_t		thrd;
	pthread_mutex_t	mutex;
}					t_philo;

struct timeval tv_init;