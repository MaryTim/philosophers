/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbudkevi <mbudkevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:24:16 by mbudkevi          #+#    #+#             */
/*   Updated: 2024/12/10 14:24:17 by mbudkevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

bool	is_space(char c)
{
	if (c == ' ' || (c >= '\t' && c <= '\r'))
		return (true);
	return (false);
}

bool	is_digit(int c)
{
	if (c >= '0' && c <= '9')
		return (true);
	return (false);
}

int	validate_input(char *argv)
{
	long	res;

	res = 0;
	while (is_space(*argv))
		argv++;
	while (*argv == '+')
		argv++;
	while (is_digit(*argv))
		res = res * 10 + *argv++ - '0';
	return (res);
}
