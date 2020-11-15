#ifndef PHILO1_H
# define PHILO1_H

#include <sys/time.h>
#include <pthread.h>
#include <stdio.h>
#include "struct.h"
#include <unistd.h>
#include <stdlib.h>

char			*ft_itoa(int n); 
int		ft_isdigit(int c);
int		ft_atoi(const char *str);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
int p_error(const char *s);
int	struct_fill(t_start *start, char **av, int ac);

#endif