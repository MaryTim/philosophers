#include "philo.h"

void	check_meals(t_data *data)
{
	t_philo	*philo;
	bool	all_full;
	int		i;

	all_full = true;
	i = 0;
	if (data->max_meals == -1)
		return ;
	while (i < data->philo_nbr)
	{
		philo = &data->philos[i];
		if (philo->meals < data->max_meals)
		{
			all_full = false;
			break ;
		}
        i++;
	}
	if (all_full)
	{
		pthread_mutex_lock(&data->mutex);
		data->is_finished = true;
		pthread_mutex_unlock(&data->mutex);
	}
}

void	has_died(t_data *data)
{
	t_philo	*philo;
	int		i;

	i = 0;
	while (i < data->philo_nbr)
	{
		philo = &data->philos[i];
		if (get_timestamp(philo->last_meal) >= (data->time_to_die / 1000)
			&& !philo->is_eating)
		{
			pthread_mutex_lock(&data->mutex);
			printf("%ld %ld died\n", get_timestamp(data->start_time), philo->id);
			data->is_finished = true;
			pthread_mutex_unlock(&data->mutex);
			return ;
		}
		usleep(1000);
        i++;
	}
}

void	*monitor(void *value)
{
	t_data	*data;

	data = (t_data *)value;
	while (!data->is_finished)
	{
		has_died(data);
		check_meals(data);
	}
	return (NULL);
}