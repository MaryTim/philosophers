/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbudkevi <mbudkevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:19:17 by mbudkevi          #+#    #+#             */
/*   Updated: 2024/12/10 14:25:35 by mbudkevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*error_handling(char *message, void *return_value)
{
	printf("Error: %s\n", message);
	return (return_value);
}

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

long	get_timestamp(long time)
{
	return (get_time() - time);
}

void	free_memory(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_nbr)
	{
		pthread_mutex_destroy(&data->philos[i].fork_1->mutex);
		pthread_mutex_destroy(&data->philos[i].fork_2->mutex);
		i++;
	}
	pthread_mutex_destroy(&data->mutex);
	free(data->philos);
	free(data->forks);
}
