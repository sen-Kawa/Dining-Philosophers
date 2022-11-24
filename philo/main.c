/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaheinz <kaheinz@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 09:34:25 by kaheinz           #+#    #+#             */
/*   Updated: 2022/11/24 14:13:09 by kaheinz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine_philo(void *str);

int	main(int argc, char **argv)
{
	t_args	*args;
//	t_philo	*philos;

	args = NULL;
//	philos = NULL;
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

	i = 0;
	while (i < args->num_philo)
	{
		pthread_create(&args->philos[i]->thread_id, NULL, &routine_philo, &args->philos[i]);
		i++;
	}
}

void	*routine_philo(void *str)
{
	(void) str;
	printf("in routine.\n");
	return (NULL);
}
