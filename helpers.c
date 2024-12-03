/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbudkevi <mbudkevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:19:17 by mbudkevi          #+#    #+#             */
/*   Updated: 2024/12/03 14:50:54 by mbudkevi         ###   ########.fr       */
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

void	write_status(t_philo *philo, t_philo_state state)
{
	long long	time;

	time = get_time() - philo->data->start_process;
	//????
	if (philo->is_max_meals)
		return ;
	if (pthread_mutex_lock(&philo->data->write_mutex) != 0)
	{
		error_handling("Failed to lock mutex in write_status");
		return ;
	}
	if (state == TAKE_FORK_1 || state == TAKE_FORK_2)
		printf("%-6ld %d has taken a fork\n", time, philo->id);
	else if (state == EAT)
		printf("%-6ld %d is eating\n", time, philo->id);
	else if (state == SLEEP)
		printf("%-6ld %d is sleeping\n", time, philo->id);
	else if (state == THINK)
		printf("%-6ld %d is thinking\n", time, philo->id);
	else if (state == DIE)
		printf("%-6ld %d has died\n", time, philo->id);
	if (pthread_mutex_unlock(&philo->data->write_mutex) != 0)
	{
		error_handling("Failed to unlock mutex in write_status");
		return ;
	}
}