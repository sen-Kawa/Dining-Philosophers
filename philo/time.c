/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaheinz <kaheinz@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 21:06:43 by kaheinz           #+#    #+#             */
/*   Updated: 2022/11/26 20:47:09 by kaheinz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int64_t	time_stamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	usleep_philo(t_args *args, int time)
{
	int64_t	end;

	end = time_stamp() + time;	
	while (args->alive == true && time_stamp() < end)
		usleep(50);
}

void	death_checker(t_args *args, t_philo *philo, int i)
{
	pthread_mutex_lock(&args->philos[i]->meal_mutex);
	pthread_mutex_lock(&args->alive_mutex);
	if (time_stamp() > philo->previous_meal + args->time_die)
	{
		args->alive = false;
		print_message(philo, "died");
		pthread_mutex_unlock(&args->alive_mutex);
		pthread_mutex_unlock(&args->philos[i]->meal_mutex);
	}
	else
	{
		pthread_mutex_unlock(&args->alive_mutex);
		pthread_mutex_unlock(&args->philos[i]->meal_mutex);
	}
}
