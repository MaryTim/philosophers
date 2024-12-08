/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbudkevi <mbudkevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 17:21:27 by mbudkevi          #+#    #+#             */
/*   Updated: 2024/12/04 16:35:49 by mbudkevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*init_monitor(t_philo *philo)
{
	t_philo	*monitor;

	monitor = malloc(sizeof(t_philo));
	if (!monitor)
		return (NULL);
	monitor->philo_id = 0;
	monitor->meals_count = philo->meals_count;
	monitor->time_to_die = philo->time_to_die;
	monitor->time_to_eat = philo->time_to_eat;
	monitor->time_to_sleep = philo->time_to_sleep;
	monitor->meals_required = philo->meals_required;
	monitor->last_meal_time = philo->last_meal_time;
	monitor->forks_nbr = philo->philos_nbr;
	monitor->philos_nbr = philo->philos_nbr;
	monitor->forks = NULL;
	monitor->state_mutex = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(monitor->state_mutex, NULL);
	return (monitor);
}

void	attach_monitor(t_philo *philos, t_philo *monitor)
{
	int	i;

	i = 0;
	while (i < monitor->philos_nbr)
	{
		philos[i].state_mutex = monitor->state_mutex;
		i++;
	}
	monitor->sim_start_time = get_time();
}


int	check_meals_completion(t_philo *monitor)
{
	int	i;

	i = 0;
	if (monitor->meals_required == -1)
		return (1);
	while (i < monitor->philos_nbr)
	{
		pthread_mutex_lock(monitor->state_mutex);
		if (monitor->meals_count[i] < monitor->meals_required)
			return (pthread_mutex_unlock(monitor->state_mutex), 1);
		pthread_mutex_unlock(monitor->state_mutex);
		i++;
	}
	pthread_mutex_lock(monitor->state_mutex);
	return (0);
}

void	*check_health(void *data)
{
	t_philo			*monitor;
	int				i;
	long long		last_meal_time;

	monitor = (t_philo *)data;
	i = 0;
	sleep_for(10);
	while (i < monitor->philos_nbr && check_meals_completion(monitor))
	{
		pthread_mutex_lock(monitor->state_mutex);
		last_meal_time = get_time() - monitor->last_meal_time[i];
		pthread_mutex_unlock(monitor->state_mutex);
		if (last_meal_time >= monitor->time_to_die)
		{
			pthread_mutex_lock(monitor->state_mutex);
			has_died(i + 1, get_time() - monitor->sim_start_time);
			return (NULL);
		}
		if (i + 1 == monitor->philos_nbr)
			i = -1;
		i++;
	}
	return (NULL);
}