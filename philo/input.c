/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaheinz <kaheinz@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 09:34:25 by kaheinz           #+#    #+#             */
/*   Updated: 2022/11/24 13:00:11 by kaheinz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	correct_input(t_args *args)
{
	if (args->num_philo > 200 || args->num_philo == 0 || args->time_die < 60 || args->time_eat < 60)
	{
		printf("Try again with more than 0 but no more than 200 philo, no less than 60 ms time to die or time to eat.\n");
		return (0);
	}
//	else if (args->num_philo == 1)
//		printf("Philosopher 1 died.\n");
	else
		return (1);
//		printf("goed bezig");
}

t_args	*argument_converter(int argc, char **argv)
{
	t_args	*args;
//	t_philo	*philos;
	int	i;

	i = 0;
	args = malloc(sizeof(t_args));
	args->num_philo = ft_atoi(argv[1]);
	args->time_die = ft_atoi(argv[2]);
	args->time_eat = ft_atoi(argv[3]);
	args->time_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		args->num_times_eat = ft_atoi(argv[5]);
	args->start_time = time_stamp();
	args->philos = malloc(sizeof(t_philo) * args->num_philo);
	while (i < args->num_philo)
	{
		args->philos[i] = malloc(sizeof(t_philo));
		args->philos[i]->philo_id = i + 1;
		args->philos[i]->times_eaten = 0;
		i++;
	}
	//initialize each philo structure
	print_arg_struct(args);
	return (args);
}

void	print_arg_struct(t_args *args)
{
	printf("Num philo %i\n", args->num_philo);
	printf("Time to die %i\n", args->time_die);
	printf("Time to eat %i\n", args->time_eat);
	printf("Time to sleep %i\n", args->time_sleep);
	printf("Number of times to eat %i\n", args->num_times_eat);
	printf("Starting time %lu\n", args->start_time);
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
