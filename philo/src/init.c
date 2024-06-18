/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgavairo <jgavairo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:18:36 by jgavairo          #+#    #+#             */
/*   Updated: 2024/06/18 15:32:46 by jgavairo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	init_one_philo(t_philosopher **philo, t_data *data, int i)
{
	(*philo)[i].id = i + 1;
	(*philo)[i].data = data;
	(*philo)[i].meals_eaten = 0;
	(*philo)[i].left_fork_bool = false;
	(*philo)[i].right_fork_bool = (*philo)[(i + 1) % \
	data->number_of_philosophers].left_fork_bool;
	(*philo)[i].last_meal = get_timestamp();
	(*philo)[i].left_fork = malloc(sizeof(pthread_mutex_t));
	if (pthread_mutex_init((*philo)[i].left_fork, NULL) != 0)
		return (-1);
	return (0);
}

int	init_philosophers(t_data *data, t_philosopher **philo)
{
	int	i;

	i = 0;
	(*philo) = malloc(sizeof(t_philosopher) * data->number_of_philosophers);
	if (!(*philo))
		return (-1);
	while (i < data->number_of_philosophers)
	{
		if (init_one_philo(philo, data, i) != 0)
			return (-1);
		i++;
	}
	i = 0;
	while (i < data->number_of_philosophers)
	{
		(*philo)[i].right_fork = ((*philo)[(i + 1) % \
		data->number_of_philosophers].left_fork);
		if (pthread_create(&((*philo)[i].thread), NULL, \
		philo_routine, &((*philo)[i])) != 0)
			return (-1);
		i++;
	}
	data->start = 1;
	return (0);
}

int	data_init(int argc, char **argv, t_data *data)
{
	if (argc < 5 || argc > 6)
		return (-1);
	data->print = malloc(sizeof(pthread_mutex_t));
	if (!data->print)
		return (-1);
	data->start = 0;
	data->number_of_philosophers = atoi(argv[1]);
	data->time_to_die = atol(argv[2]);
	data->time_to_eat = atol(argv[3]);
	data->time_to_sleep = atol(argv[4]);
	if (argv[5])
		data->number_of_meals = atol(argv[5]);
	else
		data->number_of_meals = -1;
	return (0);
}
