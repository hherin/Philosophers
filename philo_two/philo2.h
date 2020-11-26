#ifndef PHILO2_H
# define PHILO2_H

#include <sys/time.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>

int		g_stop;

#include <stdio.h> // SUPP

typedef struct		s_start
{
	long			time;
	sem_t			*fork;
	sem_t			*print;
	sem_t			*die;
	int				nb_philo;
	int				state[4];
	int				start;
	int				counter;
}					t_start;

typedef struct		s_philo
{
	long			time[2];
	int				id;
	int				meals;
	pthread_t		thrd;
	t_start			*sdata;
}					t_philo;

enum e_state {DIE, EAT, SLEEP, MEALS};

int		ft_atoi(const char *str);
int	nblen(long nb);
int		p_error(const char *s);
long	ms_time(void);
size_t ft_strlen(const char *str);
int		print_msg(const char *str, t_start *sdata, t_philo *ph);
int	print_dead(const char *str, t_start *sdata, t_philo *ph);

int		sdata_init(t_start *start, char **av, int ac); //
void	pth_create(t_philo *philo, t_start *sdata);
void	philo_init(t_philo *philo, t_start *sdata);
void	*philo_routine(void *philo);
void	better_sleep(long d);

#endif