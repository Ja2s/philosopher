/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgavairo <jgavairo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 16:20:08 by jgavairo          #+#    #+#             */
/*   Updated: 2024/06/24 16:10:19 by jgavairo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_usleep(t_data *data, long time)
{
	long i;

	i = get_timestamp();
	while (1)
	{
		if ((long)(get_timestamp - i) >= time)
			break;
		pthread_mutex_lock(&data->stop_mut);
		if (data->stop == 1)
			return (pthread_mutex_unlock(&data->stop_mut), -1);
		pthread_mutex_unlock(&data->stop_mut);
		return (-1);
		usleep(10);
	}
	return (0);
}

int	write_status(t_philosopher *philo, char *status)
{
	pthread_mutex_lock(&philo->data->time_mut);
	if (get_timestamp() - philo->last_meal > philo->data->time_to_die)
	{
		pthread_mutex_unlock(&philo->data->time_mut);
		pthread_mutex_lock(&philo->data->stop_mut);
		philo->data->stop = 1;
		pthread_mutex_unlock(&philo->data->stop_mut);
	}
	pthread_mutex_unlock(&philo->data->time_mut);
	pthread_mutex_lock(&philo->data->stop_mut);
	if (philo->data->stop == 1)
		return (pthread_mutex_unlock(&philo->data->stop_mut), -1);
	pthread_mutex_unlock(&philo->data->stop_mut);
	pthread_mutex_lock(&philo->data->print);
	pthread_mutex_lock(&philo->data->time_mut);
	printf ("| %ld | The philosopher %d %s\n", (get_timestamp() - philo->data->starting_time), philo->id, status);
	pthread_mutex_unlock(&philo->data->time_mut);
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
	pthread_mutex_lock(&data->meals);
	if (data->number_of_meals != -1 && \
	philo->meals_eaten >= data->number_of_meals)
	{
		pthread_mutex_unlock(&data->meals);
		pthread_mutex_lock(&data->stop_mut);
		data->stop = 1;
		pthread_mutex_unlock(&data->stop_mut);
		usleep(100);
		pthread_mutex_lock(&data->print);
		pthread_mutex_lock(&data->time_mut);
		printf("| %ld | The philosopher %d eats every meal! \U0001F389\n", (get_timestamp() - philo->data->starting_time), philo->id);
		pthread_mutex_unlock(&data->time_mut);
		//pthread_mutex_unlock(&data->print);
		return (-1);
	}
	pthread_mutex_unlock(&data->meals);
	return (0);
}

int	check_death(t_philosopher *philo, t_data *data)
{
	pthread_mutex_lock(&data->time_mut);
	if (get_timestamp() - philo->last_meal > philo->data->time_to_die)
	{
		pthread_mutex_unlock(&data->time_mut);
		pthread_mutex_lock(&data->stop_mut);
		data->stop = 1;
		pthread_mutex_unlock(&data->stop_mut);
		pthread_mutex_lock(&data->print);
		usleep(1000);
		pthread_mutex_lock(&data->time_mut);
		printf("| %ld | The philosopher %d is dead \U0001F480\n",(get_timestamp() - philo->data->starting_time), philo->id);
		pthread_mutex_unlock(&data->time_mut);
		pthread_mutex_unlock(&data->print);
		return (-1);
	}
	pthread_mutex_unlock(&data->time_mut);
	return (0);
}
