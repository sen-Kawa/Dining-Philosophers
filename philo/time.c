/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaheinz <kaheinz@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 21:06:43 by kaheinz           #+#    #+#             */
/*   Updated: 2022/12/01 16:20:07 by kaheinz          ###   ########.fr       */
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

int	death_checker(t_philo *philo)                                             
{
	if ((time_stamp() - philo->previous_meal) > philo->args->time_die)
	{
		pthread_mutex_lock(&philo->args->alive_mutex);
		philo->args->alive = 0;
		pthread_mutex_unlock(&philo->args->alive_mutex);
		return (1);
	}
	return (0);
}
