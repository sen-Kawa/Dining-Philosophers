/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaheinz <kaheinz@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 09:34:25 by kaheinz           #+#    #+#             */
/*   Updated: 2022/12/06 14:03:13 by kaheinz          ###   ########.fr       */
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
//	clean_mutex(&args);
	//free?
	return (0);
}

int	lone_philosopher(t_args *args)
{
	usleep(args->time_die * 1000);
	print_message(args->philos, "died");
	return (0);
}
