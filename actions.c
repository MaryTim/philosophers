#include "philo.h"

void	print_status(const char *msg, t_philo *philo, t_data *data)
{
	pthread_mutex_lock(&data->mutex);
	if (!data->is_finished)
	print_status_message(philo, msg);
		//printf("%ld %ld %s\n", get_timestamp(data->start_time), philo->id, msg);
	pthread_mutex_unlock(&data->mutex);
}

void	think(t_philo *philo)
{
	print_status_message(philo, "is thinking");
	//print_status("is thinking", philo, data);
}

void	my_sleep(t_philo *philo, t_data *data)
{
	print_status_message(philo, "is sleeping");
	//print_status("is sleeping", philo, data);
	usleep(data->time_to_sleep);
}

void	eat(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(&philo->fork_1->mutex);
	print_status_message(philo, "has taken a fork");
	//print_status("has taken a fork", philo, data);
	if (philo->fork_2->id == philo->fork_1->id)
	{
		usleep(data->time_to_die);
		print_status_message(philo, "has died");
		//print_status("has died", philo, data);
		pthread_mutex_lock(&philo->data->mutex);
		data->is_finished = true;
		pthread_mutex_lock(&philo->data->mutex);
		return ;
	}
	pthread_mutex_lock(&philo->fork_2->mutex);
	print_status_message(philo, "has taken a fork");
	//print_status("has taken a fork", philo, data);
	philo->is_eating = true;
	print_status_message(philo, "is eating");
	//print_status("is eating", philo, data);
	usleep(data->time_to_eat);
	philo->is_eating = false;
	philo->last_meal = get_time();
	philo->meals++;
	pthread_mutex_unlock(&philo->fork_1->mutex);
	pthread_mutex_unlock(&philo->fork_2->mutex);
}

void	*routine(void *value)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)value;
	data = philo->data;
	while (!data->threads_ready)
		;
	while (!data->is_finished)
	{
		eat(philo, data);
		my_sleep(philo, data);
		think(philo);
	}
	return (NULL);
}