/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgavairo <jgavairo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:24:37 by jgavairo          #+#    #+#             */
/*   Updated: 2024/06/18 15:31:43 by jgavairo         ###   ########.fr       */
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

void	philo_eat(t_philosopher *philo)
{
	take_left_fork(philo);
	while (1)
	{
		pthread_mutex_lock(philo->right_fork);
		if (philo->right_fork_bool == false)
		{
			philo->right_fork_bool = true;
			write_status(philo, "has taken a fork");
			pthread_mutex_unlock(philo->right_fork);
			write_status(philo, "eating");
			eating(philo);
			break ;
		}
		else
		{
			pthread_mutex_unlock(philo->right_fork);
			usleep(20);
		}
	}
}

void	philo_sleep(t_philosopher *philo)
{
	write_status(philo, "sleeping");
	usleep(philo->data->time_to_sleep * 1000);
	write_status(philo, "thinking");
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
		philo_eat(philo);
		philo_sleep(philo);
	}
	return (NULL);
}
