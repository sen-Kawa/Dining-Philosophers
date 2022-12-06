/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaheinz <kaheinz@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 06:27:47 by kaheinz           #+#    #+#             */
/*   Updated: 2022/12/06 16:26:57 by kaheinz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	ft_atoi(const char *str)
{
	int				sign;
	long int		result;

	result = 0;
	sign = 1;
	while (*str == ' ' || *str == '\n'
		|| *str == '\f' || *str == '\r'
		|| *str == '\t' || *str == '\v')
		str++;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
	{
		sign = 1;
		str++;
	}
	while (*str)
	{
		result = result * 10 + *str - '0';
		str++;
	}
	return (result * sign);
}

int	is_digit(char **argv)
{
	int	i;
	int	c;

	i = 1;
	while (argv[i])
	{
		c = 0;
		while (argv[i][c])
		{
			if (argv[i][c] >= '0' && argv[i][c] <= '9')
				c++;
			else
			{
				printf("Non numeric argument.\n");
				return (0);
			}
		}
		i++;
	}
	return (1);
}

void	print_message(t_philo *philo, char *message)
{
	t_args	*args;
	int64_t	current_time;

	args = philo->args;
	current_time = time_stamp() - args->start_time;
	pthread_mutex_lock(&args->print_mutex);
	pthread_mutex_lock(&args->alive_mutex);
	if (args->alive)
		printf("%ld ms %i %s\n", current_time, philo->philo_id, message);
	pthread_mutex_unlock(&args->alive_mutex);
	pthread_mutex_unlock(&args->print_mutex);
}

int64_t	time_stamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
