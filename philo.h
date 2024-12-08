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

// philo Struct
typedef struct s_philo
{
	int				philo_id;
	int				*meals_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_required;
	long long		*last_meal_time;
	int				forks_nbr;
	int				philos_nbr;
	pthread_t		thread;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*state_mutex;
	long long		sim_start_time;
}	t_philo;

int	error_handling(char *message);
bool	is_numeric(char *str);
int	str_to_int(char *str);
int	parse_input(int argc, char **argv, t_philo *inited_data);
long long	get_time(void);
t_philo	*setup_simulation(int argc, char **argv);
t_philo	*init_monitor(t_philo *philo);
void	attach_monitor(t_philo *philos, t_philo *monitor);
void	create_threads(t_philo *philos);
void	sleep_for(long long time);
void	print_status_message(t_philo *philo, char *action);
void	*check_health(void *data);
void	has_died(int philo_id, long long elapsed_time);
void	free_memory(t_philo *philos, t_philo *monitor);

#endif