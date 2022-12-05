/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaheinz <kaheinz@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 14:32:03 by kaheinz           #+#    #+#             */
/*   Updated: 2022/12/05 16:49:24 by kaheinz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_threads(t_args *args)
{
	int	i;

	i = 0;
	args->end = 0;
	args->alive = 1;
	args->start_time = time_stamp();
	if (args->num_philo == 1)
	{
		lone_philosopher(args);
		return (2);
	}
	while (i < args->num_philo)
	{
		args->philos[i].previous_meal = time_stamp();
		pthread_create(&(args->philos[i].thread_id), NULL, &routine, &(args->philos[i]));
		i++;
	}
	//dont forget to join the threads
	joining_threads(args);
	return (0);
}

void	joining_threads(t_args *args)
{
	int	i;

	i = 0;
	while (i < args->num_philo)
	{
		pthread_join(args->philos[i].thread_id, NULL);
		i++;
	}
}

void	*routine(void *data)
{
	t_philo	*philo;
	t_args	*args;

	philo = (t_philo *)data;
	args = philo->args;
	if (philo->philo_id % 2 == 0)
		usleep(args->time_eat * 1000);
	pthread_mutex_lock(&args->meal_mutex);
	philo->previous_meal = time_stamp();
	pthread_mutex_unlock(&args->meal_mutex);
//	while (1)
//	{
		//eat routine
		print_message(philo, "gotta eat");
//	}
	return (0);
}
