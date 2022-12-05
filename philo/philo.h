/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaheinz <kaheinz@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 09:48:14 by kaheinz           #+#    #+#             */
/*   Updated: 2022/12/05 13:14:35 by kaheinz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <string.h>
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
	int					alive;
	int64_t			start_time;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	alive_mutex;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	*fork_mutex;
	t_philo			*philos;
}	t_args;

typedef struct philo
{
	int				philo_id;
	int				times_eaten;
	int				l_fork;
	int				r_fork;
	int64_t			previous_meal;
	pthread_t		thread_id;
	t_args			*args;
}	t_philo;

//main.c
void		start(t_args *args);
void    joining_threads(t_args *args);
void	clean_mutex(t_philo **philo);

//ft_atoi.c
long int	ft_atoi(const char *str);

//time.c
int64_t		time_stamp(void);
void		usleep_philo(t_args *args, int time);
int    death_checker(t_philo *philo);

//print.c
void		print_message(t_philo *philo, char *message);

//routines.c
void		eat_sleep_routine(t_philo *philo);
void		*routine_philo(void *data);
int check_alive(t_philo *philo);

//input.c
t_args		*argument_converter(int argc, char **argv);
void		init_philo(t_args *args);
int			correct_input(t_args *args);
int			is_digit(char **argv);

#endif
