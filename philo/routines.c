/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaheinz <kaheinz@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 09:34:25 by kaheinz           #+#    #+#             */
/*   Updated: 2022/12/01 13:59:26 by kaheinz          ###   ########.fr       */
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
			death_checker(args);
			i++;
		}
	}
	return (NULL);
}

void	*routine_philo(void *data)
{
	t_philo	*philo;
	t_args	*args;

	philo = (t_philo *) data;
	args = philo->args;
	lone_philosopher(philo);
	if (args->num_philo == 1 || args->num_times_eat == 0)
		return (NULL);
	if (philo->philo_id % 2)
		usleep(args->time_eat * 500);
	eat_sleep_routine(philo);
	return (NULL);
}

void	thinking_routine(t_philo *philo)
{
	int	time_think;

	time_think = 0;
	print_message(philo, "is thinking");
	usleep(time_think * 1000);
}

int	check_alive(t_args *args)
{
	pthread_mutex_lock(&args->alive_mutex);
	if (args->alive == 1)
	{
		pthread_mutex_unlock(&args->alive_mutex);
		return (1);
	}
	else
	{
		pthread_mutex_unlock(&args->alive_mutex);
		return (0);
	}
}

void	eat_sleep_routine(t_philo *philo)
{
	int	r;
	int	l;
	t_args	*args;

	args = philo->args;
	r = philo->philo_id - 1;
	l = r - 1;
	if (philo->philo_id == 1)
		l = philo->args->num_philo - 1;
	while (check_alive(args))
	{
	pthread_mutex_lock(&philo->args->fork_mutex[r]);
	pthread_mutex_lock(&philo->args->fork_mutex[l]);
	print_message(philo, "has taken a fork");
	print_message(philo, "is eating");
	usleep_philo(philo->args, philo->args->time_eat);
	pthread_mutex_lock(&philo->meal_mutex);
	philo->times_eaten += 1;
	philo->previous_meal = time_stamp();
	if (philo->times_eaten == args->num_times_eat)
	{
		pthread_mutex_unlock(&philo->meal_mutex);
		pthread_mutex_unlock(&philo->args->fork_mutex[r]);
		pthread_mutex_unlock(&philo->args->fork_mutex[l]);
		return ;
	}
	pthread_mutex_unlock(&philo->meal_mutex);
	pthread_mutex_unlock(&philo->args->fork_mutex[r]);
	pthread_mutex_unlock(&philo->args->fork_mutex[l]);
	print_message(philo, "is sleeping");
	usleep_philo(philo->args, philo->args->time_sleep);
	print_message(philo, "is thinking");
	}
}
