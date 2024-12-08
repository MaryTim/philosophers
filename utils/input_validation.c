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

static int	validate_philo_count(char *arg)
{
	if (!is_numeric(arg) || str_to_int(arg) <= 0)
        return (error_handling("Invalid number of philos!"));
	return (0);
}

static int	validate_time(char *arg)
{
	if (!is_numeric(arg) || str_to_int(arg) <= 0)
        return (error_handling("Invalid time parameter!"));
	return (0);
}

static int	validate_meals_required(char *arg)
{
	if (!is_numeric(arg) || str_to_int(arg) <= 0)
	    return (error_handling("Invalid parameter of required meals!"));
	return (0);
}

static int validate_input(char **argv, int argc)
{
    if (validate_philo_count(argv[1]) != 0 || validate_time(argv[2]) != 0 || validate_time(argv[3]) != 0
        || validate_time(argv[4]) != 0 || (argc == 6 && validate_meals_required(argv[5]) != 0))
            return (-1);
    return (0);
}

int	parse_input(int argc, char **argv, t_philo *inited_data)
{
	if (argc < 5 || argc > 6)
		return (error_handling("Please check amount of input params"));
    if (validate_input(argv, argc) == 0) {
	inited_data->philos_nbr = str_to_int(argv[1]);
	inited_data->time_to_die = str_to_int(argv[2]);
	inited_data->time_to_eat = str_to_int(argv[3]);
	inited_data->time_to_sleep = str_to_int(argv[4]);
	if (argc == 6)
		inited_data->meals_required = str_to_int(argv[5]);
	else
		inited_data->meals_required = -1;
    }
	return (0);
}
