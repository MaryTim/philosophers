/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbudkevi <mbudkevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:19:17 by mbudkevi          #+#    #+#             */
/*   Updated: 2024/12/10 13:19:40 by mbudkevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	error_handling(char *message)
{
	printf("Error: %s\n", message);
	return (-1);
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

void	print_status_message(t_philo *philo, char *message)
{
	char	*colors[6];

	colors[0] = RED;
	colors[1] = GREEN;
	colors[2] = YELLOW;
	colors[3] = BLUE;
	colors[4] = MAGENTA;
	colors[5] = CYAN;
	write(1, colors[philo->id % 6],
		str_len(colors[philo->id % 6]));
	print_number_fd(get_time() - philo->data->start_time, 1);
	write(1, "\t", 1);
	write(1, "Philosopher ", 12);
	print_number_fd(philo->id, 1);
	write(1, "\t", 1);
	write(1, message, str_len(message));
	write(1, RESET, str_len(RESET));
	write(1, "\n", 1);
}

// void print_status_message(t_philo *philo, const char *message)
// {
// 	char	*colors[6];

// 	colors[0] = RED;
// 	colors[1] = GREEN;
// 	colors[2] = YELLOW;
// 	colors[3] = BLUE;
// 	colors[4] = MAGENTA;
// 	colors[5] = CYAN;
// 	// Get Philosopher's Unique Color
// 	const char *color = colors[(philo->id - 1) % 6];

// 	// Print Message with Timestamp
// 	printf("%s%-8ld Philosopher %ld %s%s\n", color, 
// 	       get_time() - philo->data->start_time, philo->id, message, RESET);

// 	fflush(stdout);  // Ensure Immediate Output
// }

void	announce_death(int philo_id, long elapsed_time)
{
	printf("%-7ld Philosopher %d\t%s\n", elapsed_time, philo_id, "has died");
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