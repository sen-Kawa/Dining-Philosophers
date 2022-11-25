/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaheinz <kaheinz@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 09:48:14 by kaheinz           #+#    #+#             */
/*   Updated: 2022/11/25 15:58:54 by kaheinz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>

typedef struct philo	t_philo;

typedef struct args
{
	int				num_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				num_times_eat;
	bool			alive;
	int64_t			start_time;
	pthread_t		main_thread;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	*fork_mutex;
	t_philo			**philos;
}	t_args;

typedef struct philo
{
	int				philo_id;
	int				times_eaten;
	int64_t			previous_meal;
	pthread_t		thread_id;
	pthread_mutex_t	meal_mutex;
	t_args			*args;
}	t_philo;

//main.c
void		start(t_args *args);

//ft_atoi.c
long int	ft_atoi(const char *str);

//time.c
int64_t		time_stamp(void);

//print.c
void		print_message(t_philo *philo, char *message);

//routines.c
void		eat_sleep_routine(t_philo *philo);
void		thinking_routine(t_philo *philo);
void		*routine_philo(void *data);
void		*main_routine(void *data);

//input.c
t_args		*argument_converter(int argc, char **argv);
void		init_philo(t_args *args);
int			correct_input(t_args *args);
int			is_digit(char **argv);
void		print_arg_struct(t_args *args);

#endif
