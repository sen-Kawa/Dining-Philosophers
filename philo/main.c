/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaheinz <kaheinz@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 09:34:25 by kaheinz           #+#    #+#             */
/*   Updated: 2022/12/06 16:52:44 by kaheinz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_args	args;

	if (argc < 5 || argc > 6)
		return (1);
	if (!argument_converter(argc, argv, &args))
		return (1);
	if (!init_philo(&args))
		return (1);
	if (!mutex_init(&args))
		return (1);
	create_threads(&args);
	clean_mutex(&args);
	freeing(&args);
	return (0);
}

int	lone_philosopher(t_args *args)
{
	usleep(args->time_die * 1000);
	print_message(args->philos, "died");
	return (0);
}

void	clean_mutex(t_args *args)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&args->print_mutex);
	pthread_mutex_destroy(&args->alive_mutex);
	pthread_mutex_destroy(&args->meal_mutex);
	while (i < args->num_philo)
	{
		pthread_mutex_destroy(&args->fork_mutex[i]);
		i++;
	}
}

void	freeing(t_args *args)
{
	free (args->philos);
	free (args->fork_mutex);
}
