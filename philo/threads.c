/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaheinz <kaheinz@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 14:32:03 by kaheinz           #+#    #+#             */
/*   Updated: 2022/12/05 15:05:39 by kaheinz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_threads(t_args *args)
{
	int	i;

	i = 0;
	args->end = 0;
	args->alive = 1;
	args->start_time = time_stamp();
	while (i < args->num_philo)
	{
		args->philos[i].previous_meal = time_stamp();
		pthread_create(&(args->philos[i].thread_id), NULL, &routine, &(args->philos[i]));
		i++;
	}
	return (0);
}
