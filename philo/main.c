/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaheinz <kaheinz@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 09:34:25 by kaheinz           #+#    #+#             */
/*   Updated: 2022/12/05 16:16:13 by kaheinz          ###   ########.fr       */
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
	if (args.num_philo == 1)
		lone_philosopher(&args);
	else
		create_threads(&args);
	return (0);
}

int	lone_philosopher(t_args *args)
{
	args->start_time = time_stamp();
	usleep(args->time_die * 1000);
	print_message(args->philos, "died");
	return 0;
}
