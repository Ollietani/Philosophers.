#include "philo.h"

void	print_message(t_philo *philo, char type)
{
	if (((philo->eat_amount < philo->info->amount) \
	 || philo->info->amount == -1) && philo->die_check != 1)
	{
		pthread_mutex_lock(&philo->info->write);
		printf("%-5lu   ", get_time() - philo->info->start_time);
		if (type == 'f')
			printf("%d has taken fork\n", philo->index + 1);
		else if (type == 'e')
			printf("%d is eating\n", philo->index + 1);
		else if (type == 's')
			printf("%d is sleeping\n", philo->index + 1);
		else if (type == 't')
			printf("%d is thinking\n", philo->index + 1);
		pthread_mutex_unlock(&philo->info->write);
	}
	if (philo->info->num == 1)
	{
		printf("%-5lu   %d died\n", get_time() \
		- philo->info->start_time, philo->index + 1);
		philo->die_check = 1;
	}
}

void	take_forks(t_philo *philo)
{
	if (philo->left_fork >= philo->right_fork)
	{
		pthread_mutex_lock(&philo->info->fork[philo->left_fork]);
		print_message(philo, 'f');
		pthread_mutex_lock(&philo->info->fork[philo->right_fork]);
		print_message(philo, 'f');
	}
	if (philo->left_fork < philo->right_fork)
	{
		pthread_mutex_lock(&philo->info->fork[philo->right_fork]);
		print_message(philo, 'f');
		pthread_mutex_lock(&philo->info->fork[philo->left_fork]);
		print_message(philo, 'f');
	}
}

void	eating(t_philo *philo)
{
	if (get_time() > philo->last_eat + philo->info->die)
	{
		pthread_mutex_lock(&philo->info->write);
		printf("%-5lu   %d died\n", get_time() - philo->info->start_time, \
		 philo->index + 1);
		philo->die_check = 1;
		return ;
	}
	philo->last_eat = get_time();
	print_message(philo, 'e');
	philo->eat_amount++;
	my_usleep(philo->info->eat);
}

void	sleeping(t_philo *philo)
{
	pthread_mutex_unlock(&philo->info->fork[philo->left_fork]);
	pthread_mutex_unlock(&philo->info->fork[philo->right_fork]);
	print_message(philo, 's');
	my_usleep(philo->info->sleep);
}

void	thinking(t_philo *philo)
{	
	print_message(philo, 't');
}
