/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaheinz <kaheinz@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 09:48:14 by kaheinz           #+#    #+#             */
/*   Updated: 2022/11/23 18:54:59 by kaheinz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct args
{
	int	num_philo;
	int	time_die;
	int	time_eat;
	int	time_sleep;
	int	num_times_eat;
	unsigned long int	start_time;
	t_philo	**philos;
}	t_args;

typedef struct philo
{
	uint32_t	id;
	pthread_t	thread;

}	t_philo;

int			is_digit(char **argv);
t_args		*argument_converter(int argc, char **argv);
long int	ft_atoi(const char *str);
void		print_arg_struct(t_args *args);
void		correct_input(t_args *args);
unsigned long int	time_stamp(void);

#endif
