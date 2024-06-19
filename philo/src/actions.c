/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgavairo <jgavairo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:24:37 by jgavairo          #+#    #+#             */
/*   Updated: 2024/06/19 16:17:44 by jgavairo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	take_left_fork(t_philosopher *philo)
{
	while (1)
	{
		pthread_mutex_lock(philo->left_fork);
		if (philo->left_fork_bool == false)
		{
			philo->left_fork_bool = true;
			pthread_mutex_unlock(philo->left_fork);
			break ;
		}
		else
		{
			pthread_mutex_unlock(philo->left_fork);
			usleep(20);
		}
	}
}

void	eating(t_philosopher *philo)
{
	philo->last_meal = get_timestamp();
	philo->meals_eaten++;
	usleep(philo->data->time_to_sleep * 1000);
	pthread_mutex_lock(philo->left_fork);
	philo->left_fork_bool = false;
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_lock(philo->right_fork);
	philo->right_fork_bool = false;
	pthread_mutex_unlock(philo->right_fork);
}

int	philo_eat(t_philosopher *philo)
{
	take_left_fork(philo);
	while (1)
	{
		pthread_mutex_lock(philo->right_fork);
		if (philo->right_fork_bool == false)
		{
			philo->right_fork_bool = true;
			if (write_status(philo, "has taken a fork \U0001F374") == -1)
				return (-1);
			pthread_mutex_unlock(philo->right_fork);
			if (write_status(philo, "eating \U0001F355") == -1)
				return (-1);
			eating(philo);
			if (philo->data->stop == 1)
				return (-1);
			break ;
		}
		else
		{
			pthread_mutex_unlock(philo->right_fork);
			usleep(20);
		}
	}
	return (0);
}

int	philo_sleep(t_philosopher *philo)
{
	if (write_status(philo, "sleeping \U0001F4A4") == -1)
		return (-1);
	usleep(philo->data->time_to_sleep * 1000);
	if (write_status(philo, "thinking \U0001F4AD") == -1)
		return (-1);
	return (0);
}

void	*philo_routine(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	while (1)
	{
		if (philo->data->start == 1)
			break ;
	}
	if (philo->id % 2 == 0)
		usleep(philo->data->time_to_eat * 1000);
	while (1)
	{
		if (philo_eat(philo) == -1)
			return (NULL);
		if (philo->data->stop == 1)
			return (NULL);
		if (philo_sleep(philo) == -1)
			return (NULL);
		if (philo->data->stop == 1)
			return (NULL);
	}
	return (NULL);
}
