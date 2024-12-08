#include "../philo.h"

static int	skip_spaces_and_sign(const char *str, int *i)
{
	int	sign;

	sign = 1;
	while ((str[*i] >= 9 && str[*i] <= 13) || str[*i] == 32)
		(*i)++;
	if (str[*i] == '-' || str[*i] == '+')
	{
		if (str[*i] == '-')
			sign *= -1;
		(*i)++;
	}
	return (sign);
}

static bool	is_digit(int c)
{
	if (c >= '0' && c <= '9')
		return (true);
	return (false);
}

bool	is_numeric(char *str)
{
	while (*str)
	{
		if (!is_digit(*str))
			return (false);
		str++;
	}
	return (true);
}

int	str_to_int(char *str)
{
	int			sign;
	int			i;
	long long	result;
	long long	prev_result;
	long long	temp;

	i = 0;
	result = 0;
	sign = skip_spaces_and_sign(str, &i);
	while (str[i] >= '0' && str[i] <= '9')
	{
		prev_result = result;
		result = result * 10 + str[i] - '0';
		temp = result / 10;
		if (temp != prev_result)
		{
			if (sign == 1)
				return (-1);
			else
				return (0);
		}
		i++;
	}
	return (sign * result);
}