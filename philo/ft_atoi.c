/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaheinz <kaheinz@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 06:27:47 by kaheinz           #+#    #+#             */
/*   Updated: 2022/11/22 18:19:06 by kaheinz          ###   ########.fr       */
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
