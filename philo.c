/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbudkevi <mbudkevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 17:21:27 by mbudkevi          #+#    #+#             */
/*   Updated: 2024/11/13 16:27:19 by mbudkevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data *data;

	if ((argc == 5) || (argc == 6))
	{
		data = malloc(sizeof(t_data));
		if (!data)
			return (error_handling("Memory allocation failed!"));
		if (init_input(data, argv, argc) != -1)
		{
		if (init_data(data) != 0)
		{
			free(data);
			return (error_handling("Init failed"));
		}
		//satrt the process
		}
		free(data);
	}
	else
		error_handling("Please check your input parameters!");
}
