/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbudkevi <mbudkevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:49:11 by mbudkevi          #+#    #+#             */
/*   Updated: 2024/11/13 16:49:23 by mbudkevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	assign_forks(t_data *data, t_philo *philo, int pos)
{
	if (philo->id % 2 == 0)
	{
		philo->fork_1 = &data->forks[pos];
		philo->fork_2 = &data->forks[(pos + 1) % data->philo_nbr];
	}
	else
	{
		philo->fork_1 = &data->forks[(pos + 1) % data->philo_nbr];
		philo->fork_2 = &data->forks[pos];
	}
}

void	init_philos(t_data *data)
{
	int		i;
	t_philo	*philo;

	data->philos = malloc(sizeof(t_philo) * data->philo_nbr);
	if (!data->philos)
		return ;
	i = 0;
	while (i < data->philo_nbr)
	{
		philo = &data->philos[i];
		philo->id = i + 1;
		philo->data = data;
		philo->is_eating = false;
		philo->meals = 0;
		assign_forks(data, philo, i);
		pthread_mutex_init(&philo->mutex, NULL);
		i++;
	}
}

void	init_forks(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(t_fork) * data->philo_nbr);
	if (!data->forks)
		return ;
	i = 0;
	while (i < data->philo_nbr)
	{
		data->forks[i].id = i;
		pthread_mutex_init(&data->forks[i].mutex, NULL);
		i++;
	}
}

void	assign_data(t_data *data, char **argv, int argc)
{
	data->is_finished = false;
	data->threads_ready = false;
	data->philo_nbr = validate_input(argv[0]);
	data->time_to_die = validate_input(argv[1]) * 1000;
	data->time_to_eat = validate_input(argv[2]) * 1000;
	data->time_to_sleep = validate_input(argv[3]) * 1000;
	if (argc == 6)
		data->max_meals = validate_input(argv[4]);
	else
		data->max_meals = -1;
	init_forks(data);
	init_philos(data);
	pthread_mutex_init(&data->mutex, NULL);
}