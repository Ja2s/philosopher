/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgavairo <jgavairo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:18:36 by jgavairo          #+#    #+#             */
/*   Updated: 2024/07/03 16:44:55 by jgavairo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	init_one_philo(t_philosopher **philo, t_data *data, int i)
{
	(*philo)[i].id = i + 1;
	(*philo)[i].data = data;
	(*philo)[i].meals_eaten = 0;
	(*philo)[i].left_fork_bool = false;
	(*philo)[i].last_meal = get_timestamp();
	(*philo)[i].left_fork = malloc(sizeof(pthread_mutex_t));
	if (pthread_mutex_init((*philo)[i].left_fork, NULL) != 0)
		return (-1);
	(*philo)[i].right_fork_bool = NULL;
	return (0);
}

void	right_fork_init(t_data *data, t_philosopher **philo)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		(*philo)[i].right_fork = ((*philo)[(i + 1) % \
		data->number_of_philosophers].left_fork);
		(*philo)[i].right_fork_bool = &((*philo)[(i + 1) % \
		data->number_of_philosophers].left_fork_bool);
		i++;
	}
}

int	thread_launcher(t_data *data, t_philosopher **philo)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		(*philo)[i].last_meal = get_timestamp();
		if (pthread_create(&((*philo)[i].thread), NULL, \
		philo_routine, &((*philo)[i])) != 0)
			return (ft_clean(data, philo), -1);
		i++;
	}
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
			return (ft_clean(data, philo), -1);
		i++;
	}
	right_fork_init(data, philo);
	if (thread_launcher(data, philo) == -1)
		return (-1);
	data->starting_time = get_timestamp();
	pthread_mutex_lock(&data->start_mut);
	data->start = 1;
	pthread_mutex_unlock(&data->start_mut);
	return (0);
}

int	mutex_initializer(t_data *data)
{
	if (pthread_mutex_init(&data->print, NULL) != 0)
		return (-1);
	if (pthread_mutex_init(&data->time_mut, NULL) != 0)
		return (-1);
	if (pthread_mutex_init(&data->stop_mut, NULL) != 0)
		return (-1);
	if (pthread_mutex_init(&data->start_mut, NULL) != 0)
		return (-1);
	if (pthread_mutex_init(&data->meals, NULL) != 0)
		return (-1);
	if (pthread_mutex_init(&data->eat_time_mut, NULL) != 0)
		return (-1);
	return (0);
}

int	values_init(char **argv, t_data *data)
{
	data->start = 0;
	data->stop = 0;
	data->max_meal = 0;
	data->number_of_philosophers = atoi(argv[1]);
	data->time_to_die = atol(argv[2]);
	data->time_to_eat = atol(argv[3]);
	data->time_to_sleep = atol(argv[4]);
	if (argv[5])
	{
		data->number_of_meals = atol(argv[5]);
		if (data->number_of_meals < 0)
			return (p_error("Error: too few meals\n"), -1);
	}
	else
		data->number_of_meals = -1;
	return (0);
}

int	data_init(int argc, char **argv, t_data *data)
{
	int	i;
	int	x;

	i = 1;
	if (argc < 5 || argc > 6)
		return (p_error("Error: not a valids arguments\n"), -1);
	while (argv[i])
	{
		x = 0;
		while (argv[i][x])
		{
			if (argv[i][x] < '0' || argv[i][x] > '9')
				return (p_error("Error: not a valids arguments\n"), -1);
			x++;
		}
		i++;
	}
	if (mutex_initializer(data) == -1)
		return (-1);
	if (values_init(argv, data) == -1)
		return (-1);
	return (0);
}
