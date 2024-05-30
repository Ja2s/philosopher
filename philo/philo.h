/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgavairo <jgavairo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 16:20:12 by jgavairo          #+#    #+#             */
/*   Updated: 2024/05/30 16:26:26 by jgavairo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>

typedef struct s_philosopher {
    int id;
    pthread_t thread;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    long last_meal;
    int meals_eaten;
    t_params *params;
} t_philosopher;

typedef struct s_params {
    int number_of_philosophers;
    long time_to_die;
    long time_to_eat;
    long time_to_sleep;
    int number_of_meals;
    pthread_mutex_t *forks;
    t_philosopher *philosophers;
} t_params;

