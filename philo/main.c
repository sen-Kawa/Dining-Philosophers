/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaheinz <kaheinz@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 09:34:25 by kaheinz           #+#    #+#             */
/*   Updated: 2022/11/24 21:29:48 by kaheinz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine_philo(void *data);

int	main(int argc, char **argv)
{
	t_args	*args;

	args = NULL;
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

	args->start_time = time_stamp();
	printf("Starting time %lu\n", args->start_time);
	i = 0;
	while (i < args->num_philo)
	{
		pthread_create(&args->philos[i]->thread_id, NULL, &routine_philo, args->philos[i]);
		i++;
	}
	i = 0;
	while (i < args->num_philo)
	{
		pthread_join(args->philos[i]->thread_id, NULL);
		i++;	
	}
	pthread_mutex_destroy(&args->print_mutex);
	i = 0;
	while (i < args->num_philo)
	{
		pthread_mutex_destroy(&args->fork_mutex[i]);
		i++;
	}
}

void	*routine_philo(void *data)
{
	t_philo	*philo;
	int64_t	current_time;
	int	r;
	int	l;

	philo = (t_philo *) data;
	r = philo->philo_id - 1;
	l = r - 1;
	if (philo->philo_id == 1)
		l = philo->args->num_philo - 1;	
	current_time = time_stamp();
	pthread_mutex_lock(&philo->args->fork_mutex[r]);
	pthread_mutex_lock(&philo->args->fork_mutex[l]);
	pthread_mutex_lock(&philo->args->print_mutex);
	printf("%lu %i\n", current_time - philo->args->start_time, philo->philo_id);
	pthread_mutex_unlock(&philo->args->print_mutex);
//	printf("Current time stamp in routine %lu\n", current_time - philo->args->start_time);
//	printf("philo id routine: %i\n", philo->philo_id);
//	printf("thread id in routine: %lu\n", (unsigned long)philo->thread_id);
	return (NULL);
}
