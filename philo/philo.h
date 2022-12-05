/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaheinz <kaheinz@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 09:48:14 by kaheinz           #+#    #+#             */
/*   Updated: 2022/12/05 15:47:00 by kaheinz          ###   ########.fr       */
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
	int				alive;
	int				end;
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

void		joining_threads(t_args *args);
void		clean_mutex(t_philo **philo);


//time.c
int64_t		time_stamp(void);
void		usleep_philo(t_args *args, int time);
int			death_checker(t_philo *philo);

//print.c
void		print_message(t_philo *philo, char *message);

//routines.c
void		eat_sleep_routine(t_philo *philo);
void		*routine(void *data);
int			check_alive(t_philo *philo);



////////////////////
//input.c
int			argument_converter(int argc, char **argv, t_args *args);
int			mutex_init(t_args *args);
int			fork_init(t_args *args);
int			init_philo(t_args *args);
int			correct_input(t_args *args);

//utils.c
long int	ft_atoi(const char *str);
int			is_digit(char **argv);

//threads.c
int			create_threads(t_args *args);

int			lone_philosopher(t_args *args);

#endif
