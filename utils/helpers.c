/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbudkevi <mbudkevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:19:17 by mbudkevi          #+#    #+#             */
/*   Updated: 2024/12/05 18:19:10 by mbudkevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	error_handling(char *message)
{
	printf("Error: %s\n", message);
	return (-1);
}

long long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	sleep_for(long long time)
{
	long long	start_time;

	start_time = get_time();
	while (get_time() - start_time < time)
		usleep(100);
}

size_t	str_len(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	print_number_fd(int n, int fd)
{
	char	c;

	if (n < 0)
	{
		write(fd, "-", 1);
		n = -n;
	}
	if (n >= 0 && n <= 9)
	{
		c = n + '0';
		write(fd, &c, 1);
	}
	else
	{
		print_number_fd(n / 10, fd);
		print_number_fd(n % 10, fd);
	}
}

void	print_status_message(t_philo *philo, char *action)
{
	char	*colors[6];

	colors[0] = RED;
	colors[1] = GREEN;
	colors[2] = YELLOW;
	colors[3] = BLUE;
	colors[4] = MAGENTA;
	colors[5] = CYAN;
	write(1, colors[philo->philo_id % 6],
		str_len(colors[philo->philo_id % 6]));
	print_number_fd(get_time() - philo->sim_start_time, 1);
	write(1, "\t", 1);
	print_number_fd(philo->philo_id, 1);
	write(1, "\t", 1);
	write(1, action, str_len(action));
	write(1, RESET, str_len(RESET));
	write(1, "\n", 1);
}

void	has_died(int philo_id, long long elapsed_time)
{
	print_number_fd(elapsed_time, 1);
	write(1, "\t", 1);
	print_number_fd(philo_id, 1);
	write(1, "\t", 1);
	write(1, "died", 4);
	write(1, "\n", 1);
}

void	free_memory(t_philo *philos, t_philo *monitor)
{
	int	i;

	i = 0;
	sleep_for(philos->time_to_die + philos->time_to_eat + philos->time_to_sleep + 100);
	while (i < philos->philos_nbr)
	{
		pthread_mutex_destroy(&philos[i].forks[i]);
		pthread_mutex_destroy(philos[i].state_mutex);
		i++;
	}
	pthread_mutex_destroy(monitor->state_mutex);
	free(philos->forks);
	free(philos->meals_count);
	free(philos->last_meal_time);
	free(philos->state_mutex);
	free(philos);
	philos = NULL;
	free(monitor);
}