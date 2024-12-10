/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbudkevi <mbudkevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 17:21:27 by mbudkevi          #+#    #+#             */
/*   Updated: 2024/12/10 14:22:45 by mbudkevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if ((argc == 5) || (argc == 6))
	{
		assign_data(&data, argv + 1, argc);
		start_process(&data);
		free_memory(&data);
	}
	else
		return ((int)(long)error_handling
			("Please check amount of your input parameters!",
			(void *)(long)-1));
	return (0);
}
