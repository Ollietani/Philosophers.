#include "philo.h"

int	ft_add_to_struct(char **argv, t_data *info)
{
	info->num = ft_atoi(*argv);
	argv++;
	info->die = ft_atoi(*argv);
	argv++;
	info->eat = ft_atoi(*argv);
	argv++;
	info->sleep = ft_atoi(*argv);
	argv++;
	if (*argv)
	{
		info->amount = ft_atoi(*argv);
		if (info->amount <= 0)
			return (3);
	}
	else
		info->amount = -1;
	if (info->num < 1 || info->die <= 0 || info->eat <= 0 || info->sleep <= 0)
		return (3);
	info->all_eat = 1;
	return (0);
}

int	ft_error(int code, t_data *info)
{
	if (code == 1)
		printf("Malloc error\n");
	if (code == 2)
		printf("Wrong number of arguments\n");
	if (code == 3)
		printf("Wrong data\n");
	if (code == 4)
		printf("Error in mutex initialisation\n");
	if (code == 5)
		printf("Error with tread creation\n");
	if (code == 6)
		printf("Error with tread joining\n");
	free(info);
	return (code);
}

void	free_memory(t_data *info)
{
	int	i;

	i = 0;
	if (info->philo)
		free(info->philo);
	if (info->fork)
	{
		while (i < info->num)
			pthread_mutex_destroy(&info->fork[i++]);
		free(info->fork);
	}
}

void	free_data(t_data *info)
{
	pthread_mutex_destroy(&info->write);
	free_memory(info);
}
