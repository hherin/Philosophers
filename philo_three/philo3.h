/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo3.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 21:42:22 by user42            #+#    #+#             */
/*   Updated: 2020/11/26 21:44:09 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO3_H
# define PHILO3_H

# include <sys/time.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <time.h>
# include <signal.h>
# include <semaphore.h>
# include <wait.h>
# include <fcntl.h>

typedef struct	s_start
{
	long		time;
	pthread_t	counter;
	sem_t		*fork;
	sem_t		*print;
	sem_t		*die;
	sem_t		*wait;
	sem_t		*meals;
	int			nb_philo;
	int			state[4];
}				t_start;

typedef struct	s_philo
{
	long		time[2];
	pid_t		pphi;
	int			id;
	int			meals;
	int			stop;
	pthread_t	thrd;
	t_start		*sdata;
}				t_philo;

enum	e_state {DIE, EAT, SLEEP, MEALS};

int		ft_atoi(const char *str);
int		p_error(const char *s);
long	ms_time(void);
size_t	ft_strlen(const char *str);
int		print_msg(const char *str, t_start *sdata, t_philo *ph);
int		sdata_init(t_start *start, char **av, int ac);
int		philo_create(t_philo *philo, t_start *sdata);
void	philo_init(t_philo *philo, t_start *sdata);
int		philo_routine(t_philo *philo);
void	better_sleep(long d);
void	*meals_counter(void *args);

#endif
