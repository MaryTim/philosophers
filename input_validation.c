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

bool	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

bool	is_sign(char c)
{
	return (c == '+' || c == '-');
}

bool	is_number(char *value)
{
	int	i;

	i = 0;
	if (is_sign(value[i]) && value[i + 1])
		i++;
	while (value[i] && is_digit(value[i]))
		i++;
	if (value[i] && !is_digit(value[i]))
		return (false);
	else
		return (true);
}

bool	only_numbers(char **argv, int i)
{
	while (argv[i])
	{
		if (!is_number(argv[i]))
		{
			print_error("Please check your input parameters ",
				"only numbers must be provided!");
			return (false);
		}
		i++;
	}
	return (true);
}

bool	check_min_max_int(long l)
{
	if (l < INT_MIN || l > INT_MAX)
	{
		print_error("Please make sure your input parameters ",
			"are within INT_MIN INT_MAX limits!");
		return (false);
	}
	return (true);
}