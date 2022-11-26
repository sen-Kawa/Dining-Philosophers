/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaheinz <kaheinz@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 09:34:25 by kaheinz           #+#    #+#             */
/*   Updated: 2022/11/26 20:23:58 by kaheinz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	lone_philosopher(t_philo *philo)
{
	if (philo->args->num_philo == 1)
	{
		usleep(philo->args->time_die * 1000);
		print_message(philo, "died");
	}
}

void	*main_routine(void *data)
{
	int		i;
	t_args	*args;

	args = (t_args *) data;
	if (args->num_philo == 1 || args->num_times_eat == 0)
		return (NULL);
	while (1)
	{
		i = 0;
		while (i < args->num_philo)
		{
			death_checker(args, args->philos[i], i);
			i++;
		}
	}
	return (NULL);
}

void	*routine_philo(void *data)
{
	t_philo	*philo;

	philo = (t_philo *) data;
	lone_philosopher(philo);
	if (philo->args->num_philo == 1 || philo->args->num_times_eat == 0)
		return (NULL);
	if (philo->args->num_times_eat > 0)
	{
		while (philo->times_eaten < philo->args->num_times_eat)
			eat_sleep_routine(philo);
	}
	else if (philo->args->num_times_eat == -1)
	{
		while (1)
			eat_sleep_routine(philo);
	}
	return (NULL);
}

void	thinking_routine(t_philo *philo)
{
	int	time_think;

	time_think = 0;
	print_message(philo, "is thinking");
	usleep(time_think * 1000);
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
	pthread_mutex_lock(&philo->meal_mutex);
	philo->times_eaten += 1;
	philo->previous_meal = time_stamp();
	pthread_mutex_unlock(&philo->meal_mutex);
	usleep_philo(philo->args, philo->args->time_eat);
	pthread_mutex_unlock(&philo->args->fork_mutex[r]);
	pthread_mutex_unlock(&philo->args->fork_mutex[l]);
	print_message(philo, "is sleeping");
	usleep_philo(philo->args, philo->args->time_sleep);
	print_message(philo, "is thinking");
}
