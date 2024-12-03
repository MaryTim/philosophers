/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbudkevi <mbudkevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 12:11:33 by mbudkevi          #+#    #+#             */
/*   Updated: 2024/12/03 12:41:34 by mbudkevi         ###   ########.fr       */
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

void	*routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->data);
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
		while (i < data->nbr_of_philo)
		{
			if (pthread_create(&data->philos[i].thread_id, NULL, &routine, &data->philos[i]) != 0)
				return (error_handling("pthread_create failed"));
			i++;
		}
		data->start_process = get_time();
		printf("time is %lld\n", data->start_process);
		if (pthread_mutex_lock(&data->data_mutex) != 0)
			return (error_handling("mutex lock failed!"));
		data->threads_ready = true;
		if (pthread_mutex_unlock(&data->data_mutex) != 0)
			return (error_handling("mutex unlock failed!"));
		i = 0;
		while (i < data->nbr_of_philo)
		{
			if (pthread_join(&data->philos[i].thread_id, NULL) != 0)
				return (error_handling("pthread_join failed"));
			i++;
		}
	}
	return (0);
}