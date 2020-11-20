#ifndef PHILO1_H
# define PHILO1_H

#include <sys/time.h>
#include <pthread.h>
#include <stdio.h>
#include "struct.h"
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

char			*ft_itoa(int n);
int		ft_isdigit(int c);
int		ft_atoi(const char *str);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
int p_error(const char *s);
long				ms_time(void);
int	sdata_init(t_start *start, char **av, int ac);
void	pth_create(t_philo **philo, t_start sdata);
void	philo_init(t_philo **philo, t_start *sdata);
void	*philo_routine(void *ph);
void	print_msg(const char *str, t_start **sdata, t_philo **philo);
void	pth_join(t_philo **philo, t_start sdata);
int		str_digit(const char *str);
void	better_sleep(long d);
void	is_sleeping(t_philo **philo, int id);
void	is_eating(t_philo **philo, int id);

#endif