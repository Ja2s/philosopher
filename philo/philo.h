/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgavairo <jgavairo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 16:20:12 by jgavairo          #+#    #+#             */
/*   Updated: 2024/06/17 16:33:47 by jgavairo         ###   ########.fr       */
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
	pthread_mutex_t		*print;
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
    int                 *start;
    t_data				*data;
}						t_philosopher;

void *philo_routine(void *arg);
