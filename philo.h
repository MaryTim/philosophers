/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbudkevi <mbudkevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 19:21:57 by mbudkevi          #+#    #+#             */
/*   Updated: 2024/12/05 18:29:07 by mbudkevi         ###   ########.fr       */
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
# include <stdint.h>
# include <string.h>
# include <stdbool.h>

# define PHILO_H

# define RESET      "\033[0m"
# define RED        "\033[31m"
# define GREEN      "\033[32m"
# define YELLOW     "\033[33m"
# define BLUE       "\033[34m"
# define MAGENTA    "\033[35m"
# define CYAN       "\033[36m"

typedef pthread_t		t_thrd;
typedef pthread_mutex_t	t_mtx;

typedef struct s_philo	t_philo;
typedef struct s_fork	t_fork;
typedef struct s_data	t_data;

typedef struct s_philo
{
	long	id;
	long	last_meal;
	long	meals;
	bool	is_eating;
	t_fork	*fork_1;
	t_fork	*fork_2;
	t_data	*data;
	t_mtx	mutex;
	t_thrd	thread;
}	t_philo;

typedef struct s_fork
{
	long	id;
	t_mtx	mutex;
}	t_fork;

typedef struct s_data
{
	long	philo_nbr;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	max_meals;
	long	start_time;
	bool	threads_ready;
	bool	is_finished;
	t_fork	*forks;
	t_philo	*philos;
	t_thrd	monitor;
	t_mtx	mutex;
}	t_data;

int	error_handling(char *message);
int	validate_input(char *argv);
void	assign_data(t_data *data, char **argv, int argc);
long	get_time(void);
long	get_timestamp(long time);
void	start_process(t_data *data);
void	*routine(void *value);
void	*monitor(void *value);
void	free_memory(t_data *data);

#endif