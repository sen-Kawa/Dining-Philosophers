/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaheinz <kaheinz@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 14:32:03 by kaheinz           #+#    #+#             */
/*   Updated: 2022/12/06 15:59:55 by kaheinz          ###   ########.fr       */
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
		pthread_create(&(args->philos[i].thread_id), NULL,
			&routine, &(args->philos[i]));
		i++;
	}
	death_checker(args);
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

void	death_checker(t_args *args)
{
	while (1)
	{
		pthread_mutex_lock(&args->meal_mutex);
		pthread_mutex_lock(&args->alive_mutex);
		if ((time_stamp() - args->philos->previous_meal) > args->time_die)
		{
			if (!args->end)
			{
				pthread_mutex_unlock(&args->alive_mutex);
				print_message(args->philos, "died.");
				pthread_mutex_lock(&args->alive_mutex);

			}
			args->alive = 0;
			args->end = 1;
			pthread_mutex_unlock(&args->meal_mutex);
			pthread_mutex_unlock(&args->alive_mutex);
			break ;
		}
		pthread_mutex_unlock(&args->meal_mutex);
		pthread_mutex_unlock(&args->alive_mutex);
		pthread_mutex_lock(&args->alive_mutex);
		if (!args->alive)
		{
			pthread_mutex_unlock(&args->alive_mutex);
			break ;
		}
		pthread_mutex_unlock(&args->alive_mutex);
	}
}
