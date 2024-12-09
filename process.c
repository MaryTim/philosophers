#include "philo.h"

void	update_data(t_data *data)
{
	int	i;

	i = 0;
	data->start_time = get_time();
	while (i < data->philo_nbr)
    {
        data->philos[i].last_meal = data->start_time;
        i++;
    }
	data->threads_ready = true;
}

void	start_process(t_data *data)
{
	int	i;

	i = 0;
	if (data->max_meals == 0)
		return ;
	while (i < data->philo_nbr)
    {
        pthread_create(&data->philos[i].thread, NULL, routine, &data->philos[i]);
        i++;
    }
	update_data(data);
	pthread_create(&data->monitor, NULL, monitor, data);
	i = 0;
	while (i < data->philo_nbr)
    {
        pthread_join(data->philos[i].thread, NULL);
        i++;
    }
	pthread_join(data->monitor, NULL);
}