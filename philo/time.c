/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaheinz <kaheinz@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 21:06:43 by kaheinz           #+#    #+#             */
/*   Updated: 2022/11/27 00:18:14 by kaheinz          ###   ########.fr       */
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

	(void)args;
	end = time_stamp() + time;	
	while (time_stamp() < end)
	{
		usleep(50);
	}
}

int	death_checker(t_args *args)
{
	int	i;
	int	flag;

	flag = 0;
	while (1)
	{
		i = 0;
		while (i < args->num_philo)
		{
			pthread_mutex_lock(&args->philos[i]->meal_mutex);
			if (args->philos[i]->times_eaten == args->num_times_eat)
			{
				flag++;
				if (flag == args->num_philo)
				{
					joining_threads(args);
					pthread_mutex_unlock(&args->philos[i]->meal_mutex);
					return (1);
				}
			}
			pthread_mutex_lock(&args->alive_mutex);
			if (args->philos[i]->previous_meal > 0 && time_stamp() > args->philos[i]->previous_meal + args->time_die && args->philos[i]->times_eaten != args->num_times_eat)
			{
				print_message(args->philos[i], "died");
				args->alive = 0;
				joining_threads(args);
				pthread_mutex_unlock(&args->alive_mutex);
				pthread_mutex_unlock(&args->philos[i]->meal_mutex);
				return (1);
			}
			else
			{
				pthread_mutex_unlock(&args->alive_mutex);
				pthread_mutex_unlock(&args->philos[i]->meal_mutex);
			}
			i++;
		}
	}
	return (0);
}
