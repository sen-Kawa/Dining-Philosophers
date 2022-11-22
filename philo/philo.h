/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaheinz <kaheinz@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 09:48:14 by kaheinz           #+#    #+#             */
/*   Updated: 2022/11/22 20:05:43 by kaheinz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>

typedef struct args
{
	int	num_philo;
	int	time_die;
	int	time_eat;
	int	time_sleep;
	int	num_times_eat;
}	t_args;

int			is_digit(char **argv);
void		argument_converter(int argc, char **argv);
long int	ft_atoi(const char *str);
void		print_arg_struct(t_args *args);
void		correct_input(t_args *args);

#endif
