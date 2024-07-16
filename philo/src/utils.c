/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgavairo <jgavairo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 13:31:51 by jgavairo          #+#    #+#             */
/*   Updated: 2024/07/16 15:00:08 by jgavairo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	death_checker(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->data->stop_mut);
	if (philo->data->stop == 1)
	{
		pthread_mutex_unlock(&philo->data->stop_mut);
		return (-1);
	}
	pthread_mutex_unlock(&philo->data->stop_mut);
	return (0);
}

int	write_status(t_philosopher *philo, char *status)
{
	if (death_checker(philo) == -1)
		return (-1);
	pthread_mutex_lock(&philo->data->print);
	printf ("%ld %d %s\n", (get_timestamp() - \
	philo->data->starting_time), philo->id, status);
	pthread_mutex_unlock(&philo->data->print);
	return (0);
}

long	get_timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + (tv.tv_usec / 1000));
}

int	check_nb_meals(t_data *data, t_philosopher *philo)
{
	pthread_mutex_lock(&philo->data->meals);
	if (data->number_of_meals != -1 && \
	philo->meals_eaten >= data->number_of_meals)
		data->max_meal = 1;
	else
		data->max_meal = 0;
	pthread_mutex_unlock(&philo->data->meals);
	return (0);
}

int	check_death(t_philosopher *philo, t_data *data)
{
	pthread_mutex_lock(&data->meals);
	if (get_timestamp() - philo->last_meal >= philo->data->time_to_die)
	{
		pthread_mutex_unlock(&data->meals);
		pthread_mutex_lock(&data->stop_mut);
		data->stop = 1;
		pthread_mutex_unlock(&data->stop_mut);
		usleep(1000);
		pthread_mutex_lock(&data->print);
		printf("%ld %d died\n", (get_timestamp() - \
		philo->data->starting_time), philo->id);
		pthread_mutex_unlock(&data->print);
		return (-1);
	}
	pthread_mutex_unlock(&data->meals);
	return (0);
}
