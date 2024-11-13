/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbudkevi <mbudkevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:28:31 by mbudkevi          #+#    #+#             */
/*   Updated: 2024/11/13 16:50:25 by mbudkevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (isneg * result);
}

int	*make_int_array(int argc, char **argv, int i)
{
	int		*res;
	int		j;
	long	nbr;

	j = 0;
	res = malloc(sizeof(int) * (argc - 1));
	if (!res)
		return (NULL);
	while (argv[i])
	{
		nbr = ft_atol(argv[i]);
		if (!check_min_max_int(nbr))
		{
			free(res);
			return (NULL);
		}
		res[j] = (int)nbr;
		i++;
		j++;
	}
	return (res);
}

int	*int_array_from_string(char	**split_res)
{
	int		*res;
	int		j;
	int		k;
	long	nbr;

	j = 0;
	k = 0;
	res = malloc(sizeof(int) * count_elements(split_res));
	if (!res)
		return (NULL);
	while (split_res[j])
	{
		nbr = ft_atol(split_res[j]);
		if (!check_min_max_int(nbr))
		{
			free(res);
			return (NULL);
		}
		res[j] = (int)nbr;
		j++;
		k++;
	}
	return (res);
}

void	check_input(t_data data, char *argv)
{
	
}