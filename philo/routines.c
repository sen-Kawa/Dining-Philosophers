/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaheinz <kaheinz@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 09:34:25 by kaheinz           #+#    #+#             */
/*   Updated: 2022/11/25 12:38:25 by kaheinz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
			thinking_routine(philo);
		}
		pthread_mutex_lock(&philo->args->print_mutex);
		printf("total times eaten %i\n", philo->times_eaten);
		pthread_mutex_unlock(&philo->args->print_mutex);
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

void	thinking_routine(t_philo *philo)
{
	int	time_think;

	time_think = 0;
	//calculation of time to think for buffering
	//if negative then be it 0
	//if too big set a max
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
	philo->times_eaten += 1;
	philo->previous_meal = time_stamp() - philo->args->start_time;
	usleep(philo->args->time_eat * 1000);
	pthread_mutex_unlock(&philo->args->fork_mutex[r]);
	pthread_mutex_unlock(&philo->args->fork_mutex[l]);
	print_message(philo, "is sleeping");
	usleep(philo->args->time_sleep * 1000);
	print_message(philo, "woke up");
}
