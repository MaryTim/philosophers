/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbudkevi <mbudkevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 12:11:33 by mbudkevi          #+#    #+#             */
/*   Updated: 2024/12/05 13:53:49 by mbudkevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_all_threads(t_data *data)
{
	while (1)
	{
		if (pthread_mutex_lock(&data->data_mutex) != 0)
		{
			error_handling("Failed to lock mutex in wait_all_threads");
			return ;
		}
		if (data->threads_ready)
		{
			if (pthread_mutex_unlock(&data->data_mutex) != 0)
				error_handling("Failed to unlock mutex in wait_all_threads");
			break ;
		}
		if (pthread_mutex_unlock(&data->data_mutex) != 0)
		{
			error_handling("Failed to unlock mutex in wait_all_threads");
			return ;
		}
	}
}

void	eat(t_philo *philo)
{
	//take fork 1
	if (pthread_mutex_lock(&philo->fork_1->fork) != 0)
	{
		error_handling("Failed to lock fork_1 in eat");
		return ;
	}
	write_status(philo, TAKE_FORK_1);
	//take fork 2
	if (pthread_mutex_lock(&philo->fork_2->fork) != 0)
	{
		error_handling("Failed to lock fork_2 in eat");
		return ;
	}
	write_status(philo, TAKE_FORK_2);
	

	// change last meal time and increase meal count
	if (pthread_mutex_lock(&philo->philo_mutex) != 0)
	{
		error_handling("Failed to lock philo_mutex in eat");
		return ;
	}
	philo->last_meal_time = get_time();
	philo->meals_count++;
	if (pthread_mutex_unlock(&philo->philo_mutex) != 0)
	{
		error_handling("Failed to unlock philo_mutex in eat");
		return ;
	}
	write_status(philo, EAT);
	usleep(philo->data->time_to_eat);
	
	//change if philo is full
	if (philo->data->nbr_max_meals > 0 && philo->data->nbr_max_meals == philo->meals_count)
	{
		if (pthread_mutex_lock(&philo->philo_mutex) != 0)
		{
			error_handling("Failed to lock philo_mutex in eat");
			return ;
		}
		philo->is_max_meals = true;
		if (pthread_mutex_unlock(&philo->philo_mutex) != 0)
		{
			error_handling("Failed to unlock philo_mutex in eat");
			return ;
		}
	}

	//unlock forks
	if (pthread_mutex_unlock(&philo->fork_1->fork) != 0)
	{
		error_handling("Failed to unlock fork_1 in eat");
		return ;
	}
	if (pthread_mutex_unlock(&philo->fork_2->fork) != 0)
	{
		error_handling("Failed to unlock fork_2 in eat");
		return ;
	}
}

void	think(t_philo *philo)
{
	write_status(philo, THINK);
}

void	*routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->data);

	//increase number of running threads
	if (pthread_mutex_lock(&philo->data->data_mutex) != 0)
	{
		error_handling("Failed to lock mutex in routine");
		return ;
	}
	philo->data->thread_running_nbr++;
	if (pthread_mutex_unlock(&philo->data->data_mutex) != 0)
	{
		error_handling("Failed to unlock mutex in routine");
		return ;
	}
	
	while(!is_process_finished(philo->data))
	{
		// if (philo->is_max_meals) //???
		// 	break ;
		//eat
		eat(philo);
		//sleep
		write_status(philo, SLEEP);
		usleep(philo->data->time_to_sleep);
		//think
		think(philo);
	}
	return (0);
}

bool	philo_died(t_philo *philo)
{
	long	elapsed;
	long	last_meal;
	bool	is_dead;

	is_dead = false;
	if (pthread_mutex_lock(&philo->philo_mutex) != 0)
	{
		error_handling("mutex lock at philo_died func failed!");
		return (false);
	}
	last_meal = philo->last_meal_time;
	if (pthread_mutex_unlock(&philo->philo_mutex) != 0)
	{
		error_handling("mutex unlock at philo_died func failed!");
		return (false);
	}

	return (is_dead);
}

void	*monitor(void *value)
{
	t_data	*data;
	int		i;

	data = (t_data *)value;
	while (!all_threads_running(data->nbr_of_philo, &data->thread_running_nbr, &data->data_mutex))
		;
	while (!is_process_finished(data))
	{
		i = 0;
		while(i < data->nbr_of_philo && !is_process_finished(data))
		{
			if (philo_died(data->philos + i))
			{
				if (pthread_mutex_lock(&data->data_mutex) != 0)
				{
					error_handling("mutex lock at monitor func failed!");
					return ;
				}
				data->end_process = true;
				if (pthread_mutex_unlock(&data->data_mutex) != 0)
				{
					error_handling("mutex unlock at monitor func failed!");
					return ;
				}
				write_status(data->philos + i, DIE);
			}
			i++;
		}
	}
	return (0);
}

int	start_process(t_data *data)
{
	int	i;

	i = 0;
	if (data->nbr_max_meals == 0)
		(error_handling("max number of meals is 0"));
	else if (data->nbr_of_philo == 1)
	{
			// handle 1 philo
	}
	else
	{
		//create all threads
		while (i < data->nbr_of_philo)
		{
			if (pthread_create(&data->philos[i].thread_id, NULL, &routine, &data->philos[i]) != 0)
				return (error_handling("pthread_create philo thread failed"));
			i++;
		}
		//monitor
		if (pthread_create(&data->monitor, NULL, &monitor, &data) != 0)
			return (error_handling("pthread_create monitor failed"));
		//start the process
		data->start_process = get_time();
		printf("time is %lld\n", data->start_process);
		//when all threads have been created threads are ready = true
		if (pthread_mutex_lock(&data->data_mutex) != 0)
			return (error_handling("mutex lock failed!"));
		data->threads_ready = true;
		if (pthread_mutex_unlock(&data->data_mutex) != 0)
			return (error_handling("mutex unlock failed!"));
		i = 0;
		// join threads (wait for the thread to finish)
		while (i < data->nbr_of_philo)
		{
			if (pthread_join(data->philos[i].thread_id, NULL) != 0)
				return (error_handling("pthread_join failed"));
			i++;
		}
	}
	return (0);
}