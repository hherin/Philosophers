#ifndef PHILO1_H
# define PHILO1_H

#include <sys/time.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

int		g_stop;

#include <stdio.h> // SUPP
typedef struct		s_start
{
	long			time;
	pthread_mutex_t	print;
	pthread_mutex_t	stop;
	int				nb_philo;
	int				die;
	int				eat;
	int				sleep;
	int				nb_meals;
	int				start;
	int				counter;
}					t_start;

typedef struct		s_philo
{
	long			time[2];
	int				id;
	int				meals;
	pthread_t		thrd;
	pthread_mutex_t	fork;
	pthread_mutex_t	pick;
	t_start			*sdata;
	void			*t_save;
}					t_philo;

int		ft_atoi(const char *str);
int		p_error(const char *s);
long	ms_time(void);
size_t ft_strlen(const char *str);
int		print_msg(const char *str, t_start *sdata, t_philo *ph);

int		sdata_init(t_start *start, char **av, int ac);
void	pth_create(t_philo **philo, t_start *sdata);
void	philo_init(t_philo **philo, t_start *sdata);
void	*philo_routine(void *philo);
void	better_sleep(long d);

#endif