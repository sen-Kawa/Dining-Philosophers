/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaheinz <kaheinz@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 09:34:25 by kaheinz           #+#    #+#             */
/*   Updated: 2022/11/27 00:01:56 by kaheinz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_message(t_philo *philo, char *message)
{
	int64_t	current_time;
	int	check;

	check = check_alive(philo->args);
	current_time = time_stamp();
	pthread_mutex_lock(&philo->args->print_mutex);
	if (check == 1 || strncmp(message, "died", 4) == 0)
		printf("%ld %i %s\n", current_time - philo->args->start_time,
		philo->philo_id, message);
	pthread_mutex_unlock(&philo->args->print_mutex);
}
