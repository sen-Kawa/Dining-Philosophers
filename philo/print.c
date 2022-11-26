/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaheinz <kaheinz@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 09:34:25 by kaheinz           #+#    #+#             */
/*   Updated: 2022/11/25 17:40:44 by kaheinz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_message(t_philo *philo, char *message)
{
	int64_t	current_time;

	current_time = time_stamp();
	pthread_mutex_lock(&philo->args->print_mutex);
	printf("%lld %i %s\n", current_time - philo->args->start_time,
		philo->philo_id, message);
	pthread_mutex_unlock(&philo->args->print_mutex);
}
