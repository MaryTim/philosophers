/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbudkevi <mbudkevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:19:17 by mbudkevi          #+#    #+#             */
/*   Updated: 2024/12/04 16:31:25 by mbudkevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error_handling(char *message)
{
	printf("Error: %s\n", message);
	return (-1);
}

long long	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
		return (error_handling("gettimeofday failed"));
	return ((long long)(tv.tv_sec) * 1000 + (long long)(tv.tv_usec) / 1000);
}

bool	is_process_finished(t_philo *philo)
{
	bool	is_process_finished;

	if (pthread_mutex_lock(&philo->data->data_mutex) != 0)
	{
		error_handling("Failed to lock mutex in write_status");
		return false;
	}
	is_process_finished = philo->data->end_process;
	if (pthread_mutex_unlock(&philo->data->data_mutex) != 0)
	{
		error_handling("Failed to unlock mutex in write_status");
		return false;
	}
	return (is_process_finished);
}

void	write_status(t_philo *philo, t_philo_state state)
{
	long long	time;

	time = get_time() - philo->data->start_process;
	//????
	//start_process(philo->data);
	if (philo->is_max_meals) //should it be thread safe?
		return ;
	if (pthread_mutex_lock(&philo->data->write_mutex) != 0)
	{
		error_handling("Failed to lock mutex in write_status");
		return ;
	}
	if (state == TAKE_FORK_1 || state == TAKE_FORK_2)
		printf("%-6lld %d has taken a fork\n", time, philo->id);
	else if (state == EAT)
		printf("%-6lld %d is eating\n", time, philo->id);
	else if (state == SLEEP)
		printf("%-6lld %d is sleeping\n", time, philo->id);
	else if (state == THINK)
		printf("%-6lld %d is thinking\n", time, philo->id);
	else if (state == DIE)
		printf("%-6lld %d has died\n", time, philo->id);
	if (pthread_mutex_unlock(&philo->data->write_mutex) != 0)
	{
		error_handling("Failed to unlock mutex in write_status");
		return ;
	}
}