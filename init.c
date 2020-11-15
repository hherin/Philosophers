#include "philo1.h"

int p_error(const char *s)
{
	int i;

	i = -1;
	while (s[++i])
		write(2, &s[i], 1);
	write(2, "\n", 1);
	return (0);
}

static int		str_digit(const char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

int	struct_fill(t_start *start, char **av, int ac)
{
	if (ac < 5)
		return (p_error("Need arguments"));
	if (!str_digit(av[1]) || !(start->nb_philo = ft_atoi(av[1])))
		return (p_error("Wrong philosopher input"));
	if (!str_digit(av[2]) || !(start->die = ft_atoi(av[2])))
		return (p_error("Wrong died input"));
	if (!str_digit(av[3]) || !(start->eat = ft_atoi(av[3])))
		return (p_error("Wrong eat input"));
	if (!str_digit(av[4]) || !(start->sleep = ft_atoi(av[4])))
		return (p_error("Wrong eat input"));
	start->nb_meals = (ac > 5) ? ft_atoi(av[5]) : -1;
	return (1);
}