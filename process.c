/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbudkevi <mbudkevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:23:20 by mbudkevi          #+#    #+#             */
/*   Updated: 2024/12/10 14:23:47 by mbudkevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		if (pthread_create(&data->philos[i].thread, NULL,
				routine, &data->philos[i]) != 0)
			error_handling("create threads failed in start process", NULL);
		i++;
	}
	update_data(data);
	if (pthread_create(&data->monitor, NULL, monitor, data) != 0)
		error_handling("create monitor failed in start process", NULL);
	i = 0;
	while (i < data->philo_nbr)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
	pthread_join(data->monitor, NULL);
}
