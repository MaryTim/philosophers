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

#include "philo.h"

bool	check_max_int(long l)
{
	if (l < 0|| l > INT_MAX)
	{
		error_handling("Please cmake sure your input params are within 0 and INT_MAX limits!");
		return (false);
	}
	return (true);
}

long	ft_atol(const char *str)
{
	int		i;
	long	result;
	long	isneg;

	i = 0;
	result = 0;
	isneg = 1;
	if (str[i] == 0)
		return (0);
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			isneg = -1;
		i++;
	}
	while (str[i] && (str[i] < '0' || str[i] > '9'))
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (isneg * result);
}

long	*make_long_array(int argc, char **argv)
{
	long		*res;
	int		i;
	int		j;
	long	nbr;

	i = 1;
	j = 0;
	res = malloc(sizeof(long) * (argc - 1));
	if (!res)
		return (NULL);
	while (argv[i])
	{
		nbr = ft_atol(argv[i]);
		if (!check_max_int(nbr))
		{
			free(res);
			return (NULL);
		}
		res[j] = nbr;
		i++;
		j++;
	}
	return (res);
}

int	init_input(t_data *data, char **argv, int argc)
{
	long *result;

	result = make_long_array(argc, argv);
	if (!result)
		return (error_handling("Please check your input params!\n"));
	data->nbr_of_philo = result[0];
	data->time_to_die = result[1] * 1000;
	data->time_to_eat = result[2] * 1000;
	data->time_to_sleep = result[3] * 1000;
	if (result[4])
		data->nbr_max_meals = result[4];
	else
		data->nbr_max_meals = -1;
	return (0);
}