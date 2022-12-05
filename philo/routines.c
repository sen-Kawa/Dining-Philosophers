/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaheinz <kaheinz@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 14:32:03 by kaheinz           #+#    #+#             */
/*   Updated: 2022/12/06 00:29:36 by kaheinz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	while (1)
	{
		if (args->num_times_eat == philo->times_eaten)
		{
			print_message(philo, "ate enough times.");
			break ;
		}
		actions(philo, args);
		pthread_mutex_lock(&args->alive_mutex);
		if (!args->alive)
		{
			pthread_mutex_unlock(&args->alive_mutex);
			break ;
		}
		pthread_mutex_unlock(&args->alive_mutex);
	}
	return (0);
}

void	actions(t_philo *philo, t_args *args)
{
	eating(philo, args);
	sleeping(philo, args);
	thinking(philo, args);
}

void	eating(t_philo *philo, t_args *args)
{
	pthread_mutex_lock(&(args->fork_mutex[philo->l_fork]));
	print_message(philo, "has taken a fork.");
	pthread_mutex_lock(&(args->fork_mutex[philo->r_fork]));
	print_message(philo, "has taken a fork.");
	print_message(philo, "is eating.");
	pthread_mutex_lock(&(args->meal_mutex));
	philo->previous_meal = time_stamp();
	pthread_mutex_unlock(&(args->meal_mutex));
	usleep(args->time_eat * 1000);
	philo->times_eaten += 1;
	pthread_mutex_unlock(&(args->fork_mutex[philo->l_fork]));
	pthread_mutex_unlock(&(args->fork_mutex[philo->r_fork]));
}	

void	sleeping(t_philo *philo, t_args *args)
{
	print_message(philo, "is sleeping.");
	usleep(args->time_sleep * 1000);
}

void	thinking(t_philo *philo, t_args *args)
{
	(void)args;
	print_message(philo, "is thinking.");
}
