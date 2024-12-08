#include "philo.h"

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->forks[philo->philo_id - 1]);
	if (philo->philo_id == 1)
		pthread_mutex_lock(&philo->forks[philo->philos_nbr - 1]);
	else
		pthread_mutex_lock(&philo->forks[philo->philo_id - 2]);
	pthread_mutex_lock(philo->state_mutex);
	print_status_message(philo, "has taken a fork");
	pthread_mutex_unlock(philo->state_mutex);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->state_mutex);
	print_status_message(philo, "is eating");
	philo->last_meal_time[philo->philo_id - 1] = get_time();
	philo->meals_count[philo->philo_id - 1]++;
	pthread_mutex_unlock(philo->state_mutex);
	sleep_for(philo->time_to_eat);
}

void	release_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->forks[philo->philo_id - 1]);
	if (philo->philo_id == 1)
		pthread_mutex_unlock(&philo->forks[philo->philos_nbr - 1]);
	else
		pthread_mutex_unlock(&philo->forks[philo->philo_id - 2]);
}

void	p_sleep(t_philo *philo)
{
	pthread_mutex_lock(philo->state_mutex);
	print_status_message(philo, "is sleeping");
	pthread_mutex_unlock(philo->state_mutex);
	sleep_for(philo->time_to_sleep);
}

void	think(t_philo *philo)
{
	pthread_mutex_lock(philo->state_mutex);
	print_status_message(philo, "is thinking");
	pthread_mutex_unlock(philo->state_mutex);
}

void	*routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->philo_id % 2 == 0)
		sleep_for(10);
	while (1)
	{
		take_forks(philo);
		eat(philo);
		release_forks(philo);
		p_sleep(philo);
		think(philo);
	}
}

void	create_threads(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos->philos_nbr)
	{
		philos[i].sim_start_time = get_time();
		pthread_create(&philos[i].thread, NULL, routine, &philos[i]);
		pthread_detach(philos[i].thread);
		i++;
	}
}