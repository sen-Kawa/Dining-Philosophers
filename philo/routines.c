/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaheinz <kaheinz@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 09:34:25 by kaheinz           #+#    #+#             */
/*   Updated: 2022/11/25 17:40:02 by kaheinz          ###   ########.fr       */
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
	int64_t	current_time;
	int64_t	difference;

	i = 0;
	args = (t_args *) data;
	if (args->num_philo == 1 || args->num_times_eat == 0)
		return (NULL);
	while (1)
	{
		current_time = time_stamp() - args->start_time;
		pthread_mutex_lock(&args->philos[i]->meal_mutex);
		difference = current_time - args->philos[i]->previous_meal;
		pthread_mutex_unlock(&args->philos[i]->meal_mutex);
		if (difference > args->time_die)
		{
			
			pthread_mutex_lock(&args->print_mutex);
			printf("%ld %i DIED---------\n", current_time, i);
			pthread_mutex_unlock(&args->print_mutex);
			pthread_mutex_lock(&args->alive_mutex);
			args->alive = false;
			pthread_mutex_unlock(&args->alive_mutex);
			break ;
		}
		if (i == args->num_philo - 1)
			i = 0;
		i++;
	}
	return (NULL);
}

void	*routine_philo(void *data)
{
	t_philo	*philo;
//	int64_t	current_time;

//	current_time = time_stamp();
	philo = (t_philo *) data;
	lone_philosopher(philo);
	if (philo->args->num_philo == 1 || philo->args->num_times_eat == 0)
		return (NULL);
	if (philo->args->num_times_eat > 0)
	{
		while (philo->times_eaten < philo->args->num_times_eat && philo->args->alive)
		{
			eat_sleep_routine(philo);
			thinking_routine(philo);
		}
		pthread_mutex_lock(&philo->args->print_mutex);
		printf("total times eaten %i\n", philo->times_eaten);
		pthread_mutex_unlock(&philo->args->print_mutex);
	}
	else if (philo->args->num_times_eat == -1)
	{
		while (philo->args->alive)
		{
			eat_sleep_routine(philo);
			thinking_routine(philo);
		}
	}
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
	usleep(philo->args->time_eat * 1000);
	pthread_mutex_lock(&philo->meal_mutex);
	philo->previous_meal = time_stamp() - philo->args->start_time;
	pthread_mutex_unlock(&philo->meal_mutex);
	pthread_mutex_unlock(&philo->args->fork_mutex[r]);
	pthread_mutex_unlock(&philo->args->fork_mutex[l]);
	print_message(philo, "is sleeping");
	usleep(philo->args->time_sleep * 1000);
}
