#include "philo1.h"
void	print_msg(const char *str, t_start **sdata, t_philo **philo)
{
	long current_time;

	current_time = ms_time();
	pthread_mutex_lock(&(*sdata)->print);
	if (!(*sdata)->dead)
		printf("%ldms\t- %d\t%s\n", current_time - (*sdata)->time, (*philo)->id + 1, str);
	pthread_mutex_unlock(&(*sdata)->print);
}
void	is_eating(t_philo **philo, int id)
{
	int lock;
	t_philo *ph_tab;

	ph_tab = (t_philo*)((*philo)->t_save);
	lock = (id % 2) ? id - 1 : id + 1;
	(id == (*philo)->sdata->nb_philo - 1) ? lock = 0 : 0;
	pthread_mutex_lock(&ph_tab[lock].mutex);
	print_msg("has taken fork", &(*philo)->sdata, philo);
	pthread_mutex_lock(&(*philo)->mutex);
	print_msg("has taken a fork", &(*philo)->sdata, philo);
	print_msg("is eating", &(*philo)->sdata, philo);
	(*philo)->time[0] = ms_time();
	better_sleep((*philo)->sdata->eat * 1000);
}

void	is_sleeping(t_philo **philo, int id)
{
	int unlock;
	t_philo *ph_tab;

	ph_tab = (t_philo*)((*philo)->t_save);
	unlock = (id % 2) ? id - 1 : id + 1;
	(id == (*philo)->sdata->nb_philo - 1) ? unlock = 0 : 0;
	pthread_mutex_unlock(&ph_tab[unlock].mutex);
	pthread_mutex_unlock(&(*philo)->mutex);
	(*philo)->time[0] = ms_time();
	print_msg("is sleeping", &(*philo)->sdata, philo);
	better_sleep((*philo)->sdata->eat * 1000);
}