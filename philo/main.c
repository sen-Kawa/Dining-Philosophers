/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaheinz <kaheinz@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 09:34:25 by kaheinz           #+#    #+#             */
/*   Updated: 2022/11/25 11:41:31 by kaheinz          ###   ########.fr       */
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
	printf("Starting time %lld\n", args->start_time);
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

void	lone_philosopher(t_philo *philo)
{
	usleep(philo->args->time_die * 1000);
	print_message(philo, "died");
}

void	*routine_philo(void *data)
{
	t_philo	*philo;
	int64_t	current_time;

	current_time = time_stamp();
	philo = (t_philo *) data;
	if (philo->args->num_philo == 1)
	{
		lone_philosopher(philo);
		return (NULL);
	}
	if (philo->args->num_times_eat == 0)
		return (NULL);
	if (philo->args->num_times_eat > 0)
	{
		while (philo->times_eaten < philo->args->num_times_eat)
		{
			eat_sleep_routine(philo);
		}
	}
/*	else if (philo->args->num_times_eat == -1)
	{
		//keep eating until death
		while ()
		{
			eat_sleep_routine(philo);
		}
	}*/
	return (NULL);
}

void	eat_sleep_routine(t_philo *philo)
{
	int	r;
	int	l;

	r = philo->philo_id - 1;
	l = r - 1;
	if (philo->philo_id == 1)
		l = philo->args->num_philo - 1;	
	pthread_mutex_lock(&philo->args->fork_mutex[r]);
	pthread_mutex_lock(&philo->args->fork_mutex[l]);
	print_message(philo, "has taken a fork");
	print_message(philo, "is eating");
	philo->times_eaten += 1;
	usleep(philo->args->time_eat * 1000);
	pthread_mutex_unlock(&philo->args->fork_mutex[r]);
	pthread_mutex_unlock(&philo->args->fork_mutex[l]);
	print_message(philo, "is sleeping");
	usleep(philo->args->time_sleep * 1000);
	print_message(philo, "woke up");
}

void	print_message(t_philo *philo, char *message)
{
	int64_t	current_time;

	current_time = time_stamp();
	pthread_mutex_lock(&philo->args->print_mutex);
	printf("%lld %i %s\n", current_time - philo->args->start_time, philo->philo_id, message);
	pthread_mutex_unlock(&philo->args->print_mutex);
}
