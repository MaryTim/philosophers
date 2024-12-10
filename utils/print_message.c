/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbudkevi <mbudkevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:25:07 by mbudkevi          #+#    #+#             */
/*   Updated: 2024/12/10 14:25:39 by mbudkevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

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

void	announce_death(int philo_id, long elapsed_time)
{
	printf("%-7ld Philosopher %d\t%s\n", elapsed_time, philo_id, "has died");
}
