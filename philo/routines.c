/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaheinz <kaheinz@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 14:32:03 by kaheinz           #+#    #+#             */
/*   Updated: 2022/12/05 23:52:16 by kaheinz          ###   ########.fr       */
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
		actions(philo, args);
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
	//grab fork
	pthread_mutex_lock(&(args->fork_mutex[philo->r_fork]));
	//grab the other damn fork
	//eat for time to eat
	//mutex for time stamp for previous meal
	//add to times eaten
	//unlock forks
}	

void	sleeping(t_philo *philo, t_args *args)
{

}

void	thinking(t_philo *philo, t_args *args)
{

}
