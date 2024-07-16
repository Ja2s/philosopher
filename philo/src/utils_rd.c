/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_rd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgavairo <jgavairo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 15:36:11 by jgavairo          #+#    #+#             */
/*   Updated: 2024/07/16 15:03:09 by jgavairo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

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

void	waiting_room(t_philosopher *philo)
{
	while (1)
	{
		pthread_mutex_lock(&philo->data->start_mut);
		if (philo->data->start == 1)
		{
			pthread_mutex_unlock(&philo->data->start_mut);
			pthread_mutex_lock(&philo->data->meals);
			philo->last_meal = get_timestamp();
			pthread_mutex_unlock(&philo->data->meals);
			break ;
		}
		pthread_mutex_unlock(&philo->data->start_mut);
		usleep (150);
	}
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	end_checker(t_data *data, t_philosopher *philo, int i)
{
	if (check_nb_meals(data, &philo[i]) == -1)
		return (-1);
	if (check_death(&philo[i], data) == -1)
		return (-1);
	return (0);
}
