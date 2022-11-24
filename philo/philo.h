/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaheinz <kaheinz@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 09:48:14 by kaheinz           #+#    #+#             */
/*   Updated: 2022/11/24 17:50:36 by kaheinz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct philo t_philo;

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
	int	philo_id;
	int	times_eaten;
	pthread_t	thread_id;
	t_args	*args;

}	t_philo;

int			is_digit(char **argv);
void		start(t_args *args);
t_args		*argument_converter(int argc, char **argv);
long int	ft_atoi(const char *str);
void		print_arg_struct(t_args *args);
int		correct_input(t_args *args);
unsigned long int	time_stamp(void);

#endif
