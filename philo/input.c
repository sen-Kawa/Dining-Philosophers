/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaheinz <kaheinz@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 09:34:25 by kaheinz           #+#    #+#             */
/*   Updated: 2022/11/25 16:00:34 by kaheinz          ###   ########.fr       */
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

t_args	*argument_converter(int argc, char **argv)
{
	t_args	*args;
	int		i;

	i = 0;
	args = malloc(sizeof(t_args));
	args->num_philo = ft_atoi(argv[1]);
	args->time_die = ft_atoi(argv[2]);
	args->time_eat = ft_atoi(argv[3]);
	args->time_sleep = ft_atoi(argv[4]);
	args->num_times_eat = -1;
	args->alive = true;
	if (argc == 6)
		args->num_times_eat = ft_atoi(argv[5]);
	args->start_time = 0;
	pthread_mutex_init(&args->print_mutex, NULL);
	args->fork_mutex = malloc(sizeof(pthread_mutex_t) * args->num_philo);
	while (i < args->num_philo)
	{
		pthread_mutex_init(&args->fork_mutex[i], NULL);
		i++;
	}
	init_philo(args);
	print_arg_struct(args);
	return (args);
}

void	init_philo(t_args *args)
{
	int	i;

	i = 0;
	args->philos = malloc(sizeof(t_philo) * args->num_philo);
	while (i < args->num_philo)
	{
		args->philos[i] = malloc(sizeof(t_philo));
		args->philos[i]->philo_id = i + 1;
		args->philos[i]->times_eaten = 0;
		args->philos[i]->previous_meal = 0;
		pthread_mutex_init(&args->philos[i]->meal_mutex, NULL);
		args->philos[i]->args = args;
		i++;
	}
}

void	print_arg_struct(t_args *args)
{
	printf("GENERAL DATA\n");
	printf("Num philo %i\n", args->num_philo);
	printf("Time to die %i\n", args->time_die);
	printf("Time to eat %i\n", args->time_eat);
	printf("Time to sleep %i\n", args->time_sleep);
	printf("Number of times to eat %i\n", args->num_times_eat);
	printf("\n");
}

int	is_digit(char **argv)
{
	int	i;
	int	c;

	i = 1;
	while (argv[i])
	{
		c = 0;
		while (argv[i][c])
		{
			if (argv[i][c] >= '0' && argv[i][c] <= '9')
				c++;
			else
				return (0);
		}
		i++;
	}
	return (1);
}
