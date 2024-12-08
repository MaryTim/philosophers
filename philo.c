/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbudkevi <mbudkevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 17:21:27 by mbudkevi          #+#    #+#             */
/*   Updated: 2024/12/04 16:35:49 by mbudkevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_philo	*philos;
	t_philo	*monitor;

	if ((argc == 5) || (argc == 6))
	{
        philos = setup_simulation(argc, argv);
        if (!philos)
            return (error_handling("Simulation init failed.\n"));
        printf("data:%lld\n ", philos[0].last_meal_time[0]);
        monitor = init_monitor(philos);
        if (!monitor)
             return (error_handling("Monitor init failed.\n"));
        attach_monitor(philos, monitor);
        create_threads(philos);
        pthread_create(&monitor->thread, NULL, check_health, monitor);
        pthread_join(monitor->thread, NULL);
        return (free_memory(philos, monitor), 0);
	}
	else
		error_handling("Please check amount of your input parameters!");
}

