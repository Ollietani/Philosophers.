#include "philo.h"

static int	ft_num(const char *s)
{
	long long int	number;

	number = 0;
	while (*s >= '0' && *s <= '9')
	{
		number = number * 10 + *s - '0';
		s++;
	}
	return (number);
}

int	ft_atoi(const char *str)
{
	long long int	number;
	int				min;

	min = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (!((*str >= '0' && *str <= '9') || *str == '+' || *str == '-'))
		return (0);
	if ((*str == '+' || *str == '-') && \
	!(*(str + 1) >= '0' && (*(str + 1) <= '9')))
		return (0);
	if (*str == '-')
	{
		min = 1;
		str++;
	}
	if (*str == '+')
		str++;
	number = ft_num(str);
	if (min == 1)
		number = -number;
	return (number);
}

void	my_usleep(unsigned long time)
{
	unsigned long	begin;

	begin = get_time();
	while (get_time() - begin < time)
		usleep(100);
}

unsigned long	get_time(void)
{
	long			ms;
	struct timeval	time;

	gettimeofday(&time, NULL);
	ms = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (ms);
}

int	ft_malloc_data(t_data *info)
{
	info->philo = malloc(sizeof(t_philo) * info->num);
	if (!info->philo)
		return (1);
	info->fork = malloc(sizeof(pthread_mutex_t) * info->num);
	if (!info->fork)
		return (1);
	return (0);
}
