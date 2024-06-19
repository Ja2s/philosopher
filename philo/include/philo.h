/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgavairo <jgavairo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 16:20:12 by jgavairo          #+#    #+#             */
/*   Updated: 2024/06/19 16:20:20 by jgavairo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdbool.h>

typedef struct s_data
{
	int					number_of_philosophers;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	int					number_of_meals;
	int					start;
	int					stop;
	pthread_mutex_t		stop_mut;
	pthread_mutex_t		print;
	long				starting_time;
}						t_data;

typedef struct s_philosopher
{
	int					id;
	pthread_t			thread;
	pthread_mutex_t		*left_fork;
	bool				left_fork_bool;
	pthread_mutex_t		*right_fork;
	bool				right_fork_bool;
	long				last_meal;
	int					meals_eaten;
	int					*start;
	t_data				*data;
}						t_philosopher;

void	take_left_fork(t_philosopher *philo);
void	eating(t_philosopher *philo);
int		philo_eat(t_philosopher *philo);
int		philo_sleep(t_philosopher *philo);
void	*philo_routine(void *arg);
int		write_status(t_philosopher *philo, char *status);
long	get_timestamp(void);
int		check_nb_meals(t_data *data, t_philosopher *philo);
int		check_death(t_philosopher *philo, t_data *data);
int		init_one_philo(t_philosopher **philo, t_data *data, int i);
int		init_philosophers(t_data *data, t_philosopher **philo);
int		data_init(int argc, char **argv, t_data *data);
