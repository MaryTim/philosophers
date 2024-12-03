/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbudkevi <mbudkevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 12:11:24 by mbudkevi          #+#    #+#             */
/*   Updated: 2024/12/03 12:11:26 by mbudkevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	assign_forks(t_philo *philo, t_fork *forks, int philo_pos)
{
	philo->fork_1 = &forks[(philo_pos + 1) % philo->data->nbr_of_philo];
	philo->fork_2 = &forks[philo_pos];
	if (philo->id % 2 == 0)
	{
		philo->fork_1 = &forks[philo_pos];
		philo->fork_2 = &forks[(philo_pos + 1) % philo->data->nbr_of_philo];
	}
}

static void	init_philo(t_data *data)
{
	int		i;
	t_philo	*philo;

	i = 0;
	while (i < data->nbr_of_philo)
	{
		philo = data->philos + i;
		philo->id = i + 1;
		philo->meals_count = 0;
		philo->is_max_meals = false;
		philo->data = data;
		philo->last_meal_time = 0;
		assign_forks(philo, data->forks, i);
		i++;
	}
}

int	init_data(t_data *data)
{
	int	i;

	i = 0;
	data->end_process = false;
	data->threads_ready = false;
	data->philos = malloc(sizeof(t_philo) * data->nbr_of_philo);
	if (pthread_mutex_init(&data->data_mutex, NULL) != 0)
			return (error_handling("Something went wrong with data mutex init"));
	if (!(data->philos))
		return (-1);
	data->forks = malloc(sizeof(t_fork) * data->nbr_of_philo);
	if (!(data->forks))
		return (-1);
	while (i < data->nbr_of_philo)
	{
		if (pthread_mutex_init(&data->forks[i].fork, NULL) != 0)
			return (error_handling("Something went wrong with forks mutex init"));
		data->forks[i].fork_id = i;
		i++;
	}
	init_philo(data);
	return (0);
}