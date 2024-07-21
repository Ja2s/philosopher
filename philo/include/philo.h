/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgavairo <jgavairo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 16:20:12 by jgavairo          #+#    #+#             */
/*   Updated: 2024/07/21 18:09:41 by jgavairo         ###   ########.fr       */
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
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				starting_time;
	int					number_of_meals;
	int					number_of_philosophers;
	int					start;
	int					stop;
	int					max_meal;
	pthread_mutex_t		stop_mut;
	pthread_mutex_t		eat_time_mut;
	pthread_mutex_t		time_mut;
	pthread_mutex_t		print;
	pthread_mutex_t		meals;
	pthread_mutex_t		start_mut;
}						t_data;

typedef struct s_philosopher
{
	int					id;
	pthread_t			thread;
	pthread_mutex_t		*left_fork;
	bool				left_fork_bool;
	pthread_mutex_t		*right_fork;
	bool				*right_fork_bool;
	long				last_meal;
	int					meals_eaten;
	int					*start;
	t_data				*data;
}						t_philosopher;

int		take_left_fork(t_philosopher *philo);
int		eating(t_philosopher *philo);
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
void	ft_clean(t_data *data, t_philosopher **philo);
void	ft_usleep_check(t_philosopher *philo, int time);
int		death_checker(t_philosopher *philo);
void	p_error(char *str);
int		mutex_initializer(t_data *data);
void	program_stopper(t_philosopher *philo, t_data *data);
int		parser(t_data *data);
void	waiting_room(t_philosopher *philo);
int		end_checker(t_data *data, t_philosopher *philo, int i);
int		ft_strlen(char *str);
int		thread_launcher(t_data *data, t_philosopher **philo);
int		ft_atol(const char *str);