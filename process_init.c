#include "philo.h"

pthread_mutex_t	*init_forks(int philos_nbr)
{
	int				i;
	pthread_mutex_t	*forks;

	i = 0;
	forks = malloc(sizeof(pthread_mutex_t) * philos_nbr);
	if (!forks)
		return (NULL);
	while (i < philos_nbr)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	return (forks);
}

long long	*init_last_meal_time(int philos_nbr)
{
	int			i;
	long long	*last_meal_times;

	i = 0;
	last_meal_times = malloc(sizeof(long long) * philos_nbr);
	if (!last_meal_times)
		return (NULL);
	while (i < philos_nbr)
	{
		last_meal_times[i] = get_time();
		i++;
	}
	return (last_meal_times);
}

void	set_philo_data(t_philo *philos, t_philo *inited_data, pthread_mutex_t *forks, long long *last_meal_time)
{
	int	i;
	int	*meals;

	meals = malloc(sizeof(int) * inited_data->philos_nbr);
	if (!meals)
		return ;
	memset(meals, 0, sizeof(int) * inited_data->philos_nbr);
	i = 0;
	while (i < inited_data->philos_nbr)
	{
		philos[i].philo_id = i + 1;
		philos[i].meals_count = meals;
		philos[i].time_to_die = inited_data->time_to_die;
		philos[i].time_to_eat = inited_data->time_to_eat;
		philos[i].time_to_sleep = inited_data->time_to_sleep;
		philos[i].meals_required = inited_data->meals_required;
		philos[i].last_meal_time = last_meal_time;
		philos[i].forks_nbr = inited_data->philos_nbr;
		philos[i].philos_nbr = inited_data->philos_nbr;
		philos[i].forks = forks;
		i++;
	}
	free(inited_data);
}

t_philo	*init_philo(t_philo *inited_data)
{
	t_philo			*philos;
	pthread_mutex_t	*forks;
	long long		*last_meal_time;

	philos = malloc(sizeof(t_philo) * inited_data->philos_nbr);
	if (!philos)
		return (NULL);
	forks = init_forks(inited_data->philos_nbr);
	last_meal_time = init_last_meal_time(inited_data->philos_nbr);
	set_philo_data(philos, inited_data, forks, last_meal_time);
	return (philos);
}


t_philo	*setup_simulation(int argc, char **argv)
{
	t_philo	*inited_data;
	t_philo	*philos;

	inited_data = malloc(sizeof(t_philo));
	if (!inited_data)
		return (NULL);
	if (parse_input(argc, argv, inited_data) != 0)
	{
		free(inited_data);
		return (NULL);
	}
	philos = init_philo(inited_data);
	if (!philos)
	{
		free(inited_data);
		return (NULL);
	}
	return (philos);
}