#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>

typedef struct s_philo
{
	int				index;
	int				right_fork;
	int				left_fork;
	unsigned long	last_eat;
	unsigned long	time_to_die;
	pthread_t		id;
	int				eat_amount;
	int				die_check;
	struct s_data	*info;
}					t_philo;

typedef struct s_data
{
	int				skip;
	unsigned long	time_of_death;
	int				num;
	unsigned long	die;
	unsigned long	eat;
	unsigned long	sleep;
	int				amount;
	unsigned long	start_time;
	pthread_mutex_t	*fork;
	pthread_mutex_t	write;
	pthread_mutex_t	check_death;
	struct s_philo	*philo;
	int				all_eat;
}					t_data;

int				ft_error(int code, t_data *info);
int				ft_atoi(const char *str);
int				ft_add_to_struct(char **argv, t_data *phs);
void			check_philo(t_philo *philo);
int				init_philo(t_data *info);
int				create_tread(t_data *info);
void			*doing(void *pointer);
void			sleeping(t_philo *philo);
void			eating(t_philo *philo);
void			thinking(t_philo *philo);
void			print_message(t_philo *philo, char type);
void			take_forks(t_philo *philo);
void			free_memory(t_data *info);
void			free_data(t_data *info);
unsigned long	get_time(void);
void			my_usleep(unsigned long time);
int				ft_malloc_data(t_data *info);

#endif