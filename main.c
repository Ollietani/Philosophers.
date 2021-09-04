#include "philo.h"

int	init_philo(t_data *info)
{
	int	i;

	i = 0;
	if (ft_malloc_data(info))
		return (1);
	while (i < info->num)
	{
		info->philo[i].info = info;
		info->philo[i].index = i;
		info->philo[i].left_fork = i;
		if (i < info->num - 1)
			info->philo[i].right_fork = i + 1;
		else
			info->philo[i].right_fork = 0;
		if (pthread_mutex_init(&(info->fork[i]), NULL))
			return (4);
		info->philo[i].eat_amount = 0;
		info->philo[i].die_check = 0;
		info->philo[i].last_eat = 0;
		i++;
	}
	return (0);
}

void	*doing(void *pointer)
{
	t_philo			*philo;

	philo = pointer;
	if (philo->index % 2 == 0)
		usleep(100);
	philo->last_eat = get_time();
	while ((philo->info->amount == -1 \
	|| philo->eat_amount < philo->info->amount) && philo->die_check != 1)
	{
		take_forks(philo);
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (0);
}

void	if_someone_die(t_data *info)
{
	int	true;
	int	i;
	int	a;

	true = 1;
	while (true)
	{
		i = 0;
		a = 0;
		while (i < info->num)
		{
			if (info->philo[i].eat_amount >= info->amount)
				a++;
			if (info->philo[i].die_check == 1)
				true = 0;
			i++;
		}
		if (a == info->num && info->amount != -1)
		{
			true = 0;
			printf("\nAll philosophers has eaten %d times\n", info->amount);
		}
	}
}

int	create_tread(t_data *info)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&info->write, NULL))
		return (4);
	if (pthread_mutex_init(&info->check_death, NULL))
		return (4);
	info->start_time = get_time();
	while (i < info->num)
	{
		if (pthread_create(&(info->philo[i].id), NULL, doing, &info->philo[i]))
			return (5);
		pthread_detach(info->philo[i].id);
		i++;
	}
	usleep(200);
	if_someone_die(info);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	*info;
	int		state;

	info = malloc(sizeof(t_data));
	if (!info)
		return (ft_error(1, info));
	if (argc < 5 || argc > 6)
		return (ft_error(2, info));
	if (ft_add_to_struct(++argv, info))
		return (ft_error(3, info));
	state = init_philo(info);
	if (state)
	{
		free_memory(info);
		return (ft_error(state, info));
	}
	state = create_tread(info);
	if (state)
	{
		free_memory(info);
		return (ft_error(state, info));
	}
	free_data(info);
}
