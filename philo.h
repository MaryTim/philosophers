/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbudkevi <mbudkevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 19:21:57 by mbudkevi          #+#    #+#             */
/*   Updated: 2024/12/03 14:50:30 by mbudkevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <sys/time.h>
# include <limits.h>

# define PHILO_H

typedef pthread_mutex_t t_mutex;
typedef struct s_data t_data;

typedef struct s_fork
{
	t_mutex	fork;
	int		fork_id;
}	t_fork;

typedef enum e_philo_state
{
	EAT,
	SLEEP,
	THINK,
	TAKE_FORK_1,
	TAKE_FORK_2,
	DIE
}	t_philo_state;

typedef struct s_philo
{
	int			id;
	long		meals_count;
	bool		is_max_meals;
	long		last_meal_time;
	t_fork		*fork_1;
	t_fork		*fork_2;
	pthread_t	thread_id;
	t_data		*data;
}	t_philo;

typedef struct s_data
{
	t_fork	*forks;
	t_philo	*philos;
	long	nbr_of_philo;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	nbr_max_meals;
	long long	start_process;
	bool	end_process;
	bool	threads_ready;
	t_mutex	data_mutex;
	t_mutex	write_mutex;
}	t_data;

int			error_handling(char *message);
int			init_input(t_data *data, char **argv, int argc);
int			init_data(t_data *data);
long long	get_time(void);
int			start_process(t_data *data);
void		write_status(t_philo *philo, t_philo_state state);

#endif