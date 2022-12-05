/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaheinz <kaheinz@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 09:34:25 by kaheinz           #+#    #+#             */
/*   Updated: 2022/12/05 14:59:16 by kaheinz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	correct_input(t_args *args)
{
	if (args->num_philo > 200 || args->num_philo == 0
		|| args->time_die < 60 || args->time_eat < 60)
	{
		printf("Try again with more than 0 but no more than 200 philo,");
		printf("no less than 60 ms time to die or time to eat.\n");
		return (0);
	}
	else
		return (1);
}

int	argument_converter(int argc, char **argv, t_args *args)
{
	if (!is_digit(argv))
		return (0);
	args->num_philo = ft_atoi(argv[1]);
	args->time_die = ft_atoi(argv[2]);
	args->time_eat = ft_atoi(argv[3]);
	args->time_sleep = ft_atoi(argv[4]);
	args->num_times_eat = -1;
	if (argc == 6)
		args->num_times_eat = ft_atoi(argv[5]);
	if (!correct_input(args))
		return (0);
	return (1);
}

int	mutex_init(t_args *args)
{
	if (!fork_init(args))
		return (0);
	if (pthread_mutex_init(&args->print_mutex, NULL) != 0)
	{
		printf("Error initializing printing mutex.\n");
		return (0);
	}
	if (pthread_mutex_init(&args->alive_mutex, NULL) != 0)
	{
		printf("Error initializing alive mutex.\n");
		return (0);
	}
	if (pthread_mutex_init(&args->meal_mutex, NULL) != 0)
	{
		printf("Error initializing meal mutex.\n");
		return (0);
	}
	return (1);
}

int	fork_init(t_args *args)
{
	int	i;

	i = 0;
	args->fork_mutex = malloc(sizeof(pthread_mutex_t) * args->num_philo);
	if (!args->fork_mutex)
		return (0);
	while (i < args->num_philo)
	{
		if (pthread_mutex_init(&(args->fork_mutex[i]), NULL) != 0)
		{
			printf("Error initializing fork mutex %i.\n", i);
			return (0);
		}
		i++;
	}
	return (1);
}

int	init_philo(t_args *args)
{
	int	i;

	i = 0;
	args->philos = malloc(sizeof(t_philo) * args->num_philo);
	if (!args->philos)
		return (0);
	while (i < args->num_philo)
	{
		args->philos[i].philo_id = i + 1;
		args->philos[i].times_eaten = 0;
		args->philos[i].l_fork = i;
		args->philos[i].r_fork = (i + 1) % args->num_philo;
		args->philos[i].previous_meal = 0;
		args->philos[i].args = args;
		i++;
	}
	return (1);
}
