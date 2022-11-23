/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaheinz <kaheinz@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 09:34:25 by kaheinz           #+#    #+#             */
/*   Updated: 2022/11/23 11:50:32 by kaheinz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		printf("./philo <#philo> <time_die> <time_eat> <time_sleep> <opt # times_eat>\n");
		return (1);
	}
	else if (!is_digit(argv))
	{
		printf("Not integer arguments.\n");
		return (1);
	}
	else
	{
		argument_converter(argc, argv);
	}
	return (0);
}

void	correct_input(t_args *args)
{
	if (args->num_philo > 200 || args->num_philo == 0 || args->time_die < 60 || args->time_eat < 60)
	{
		printf("Try again with more than 0 but no more than 200 philo, no less than 60 ms time to die or time to eat.\n");
		return ;
	}
	else if (args->num_philo == 1)
		printf("Philosopher 1 died.\n");
	else
		printf("goed bezig");
}

void	argument_converter(int argc, char **argv)
{
	t_args	*args;

	args = malloc(sizeof(t_args));
	args->num_philo = ft_atoi(argv[1]);
	args->time_die = ft_atoi(argv[2]);
	args->time_eat = ft_atoi(argv[3]);
	args->time_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		args->num_times_eat = ft_atoi(argv[5]);
	args->start_time = time_stamp();
	correct_input(args);
	print_arg_struct(args);
	//free args;
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
