/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaheinz <kaheinz@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 09:34:25 by kaheinz           #+#    #+#             */
/*   Updated: 2022/12/01 16:34:50 by kaheinz          ###   ########.fr       */
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
	while (check_alive(philo))
	{	 
		if (philo->times_eaten == args->num_times_eat)
		{
			print_message(philo, "has eaten enough.");
			return (0);
		}
		death_checker(philo);
		usleep(100);
		eat_sleep_routine(philo);
	}
	return (NULL);
}

int	check_alive(t_philo *philo)
{
	int	ret;

	ret = 1;
	pthread_mutex_lock(&philo->args->alive_mutex);
	if (philo->args->alive == 0)
		ret = 0;	
	pthread_mutex_unlock(&philo->args->alive_mutex);
	return (ret);
}

void	eat_sleep_routine(t_philo *philo)
{
	t_args	*args;

	args = philo->args;
	pthread_mutex_lock(&args->fork_mutex[philo->l_fork]);
	print_message(philo, "has taken a fork");
	pthread_mutex_lock(&args->fork_mutex[philo->r_fork]);
	print_message(philo, "has taken a fork");
	death_checker(philo);	
	print_message(philo, "is eating");
	usleep_philo(args, args->time_eat);
	pthread_mutex_lock(&philo->meal_mutex);
	philo->times_eaten += 1;
	philo->previous_meal = time_stamp();
	pthread_mutex_unlock(&philo->meal_mutex);
	pthread_mutex_unlock(&args->fork_mutex[philo->l_fork]);
	pthread_mutex_unlock(&args->fork_mutex[philo->r_fork]);
	death_checker(philo);	
	print_message(philo, "is sleeping");
	usleep_philo(args, args->time_sleep);
	print_message(philo, "is thinking");
	death_checker(philo);	
}
