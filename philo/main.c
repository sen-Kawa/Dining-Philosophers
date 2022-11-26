/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaheinz <kaheinz@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 09:34:25 by kaheinz           #+#    #+#             */
/*   Updated: 2022/11/27 00:01:44 by kaheinz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_args	*args;

	args = NULL;
	if (argc < 5 || argc > 6)
	{
		printf("./philo <#philo> <t_die> <t_eat> <t_sleep> <opt #t_eat>\n");
		return (1);
	}
	else if (!is_digit(argv))
	{
		printf("Not integer arguments.\n");
		return (1);
	}
	else
	{
		args = argument_converter(argc, argv);
		if (correct_input(args))
			start(args);
		free(args);
	}
	return (0);
}

void	start(t_args *args)
{
	int	i;

	args->start_time = time_stamp();
	i = 0;
//	pthread_create(&args->main_thread, NULL, &main_routine, args);
	while (i < args->num_philo)
	{
		pthread_create(&args->philos[i]->thread_id, NULL,
			&routine_philo, args->philos[i]);
		i++;
	}
	if (args->num_philo > 1)
	{
		if (!death_checker(args))
			joining_threads(args);
	}
	else
		joining_threads(args);
//	pthread_join(args->main_thread, NULL);
	pthread_mutex_destroy(&args->alive_mutex);
	pthread_mutex_destroy(&args->print_mutex);
	i = 0;
	while (i < args->num_philo)
	{
		pthread_mutex_destroy(&args->fork_mutex[i]);
		i++;
	}
}

void	joining_threads(t_args *args)
{
	int	i;

	i = 0;
	while (i < args->num_philo)
	{
		pthread_join(args->philos[i]->thread_id, NULL);
		i++;
	}
}
