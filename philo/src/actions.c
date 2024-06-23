/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgavairo <jgavairo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:24:37 by jgavairo          #+#    #+#             */
/*   Updated: 2024/06/23 18:19:38 by jgavairo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	take_left_fork(t_philosopher *philo)
{
	while (1)
	{
		pthread_mutex_lock(philo->left_fork);
		if (philo->left_fork_bool == false)
		{
			philo->left_fork_bool = true;
			pthread_mutex_unlock(philo->left_fork);
			return (0);
		}
		else
		{
			pthread_mutex_unlock(philo->left_fork);
			usleep(20);
		}
		usleep(1000); //-------------------
	}
}

void	eating(t_philosopher *philo)
{
	long	time;
	pthread_mutex_lock(&philo->data->time_mut);
	if ((get_timestamp() - philo->last_meal) > philo->data->time_to_die)
	{
		pthread_mutex_unlock(&philo->data->time_mut);
		pthread_mutex_lock(&philo->data->stop_mut);
		philo->data->stop = 1;
		pthread_mutex_unlock(&philo->data->stop_mut);
		return ;
	}
	pthread_mutex_unlock(&philo->data->time_mut);
	pthread_mutex_lock(&philo->data->meals);
	philo->last_meal = get_timestamp();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->meals);
	pthread_mutex_lock(&philo->data->eat_time_mut);
	time = (philo->data->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->data->eat_time_mut);
	usleep(time);
	pthread_mutex_lock(philo->left_fork);
	philo->left_fork_bool = false;
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_lock(philo->right_fork);
	philo->right_fork_bool = false;
	pthread_mutex_unlock(philo->right_fork);
}

int	philo_eat(t_philosopher *philo)
{
	while (1)
	{
		pthread_mutex_lock(&philo->data->time_mut);
		if (get_timestamp() - philo->last_meal > philo->data->time_to_die)
		{
			pthread_mutex_unlock(&philo->data->time_mut);
			pthread_mutex_lock(&philo->data->stop_mut);
			philo->data->stop = 1;
			pthread_mutex_unlock(&philo->data->stop_mut);
			return (-1);
		}
		pthread_mutex_unlock(&philo->data->time_mut);
		if (take_left_fork(philo) == 0)
		{	
			pthread_mutex_lock(philo->right_fork);
			if (philo->right_fork_bool == false)
			{
				philo->right_fork_bool = true;
				pthread_mutex_unlock(philo->right_fork);
				if (write_status(philo, "has taken a fork \U0001F374") == -1)
					return (-1);
				if (write_status(philo, "eating \U0001F355") == -1)
					return (-1);
				eating(philo);
				pthread_mutex_lock(&philo->data->stop_mut);
				if (philo->data->stop == 1)
					return (pthread_mutex_unlock(&philo->data->stop_mut), -1);
				pthread_mutex_unlock(&philo->data->stop_mut);	
				break ;
			}
			else
			{
				pthread_mutex_unlock(philo->right_fork);
				pthread_mutex_lock(philo->left_fork);
				philo->left_fork_bool = false;
				pthread_mutex_unlock(philo->left_fork);
				usleep(100);
			}
		}
		usleep(1000); //-------------------
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
		pthread_mutex_lock(&philo->data->start_mut);
		if (philo->data->start == 1)
		{
			pthread_mutex_unlock(&philo->data->start_mut);
			break ;
		}
		pthread_mutex_unlock(&philo->data->start_mut);
		usleep(1000); //-------------------
	}
	if (philo->id % 2 == 0)
		usleep(philo->data->time_to_eat * 1000);
	while (1)
	{
		if (philo_eat(philo) == -1)
			return (NULL);
		pthread_mutex_lock(&philo->data->stop_mut);
		if (philo->data->stop == 1)
			return (pthread_mutex_unlock(&philo->data->stop_mut), NULL);
		pthread_mutex_unlock(&philo->data->stop_mut);
		if (philo_sleep(philo) == -1)
			return (NULL);
		pthread_mutex_lock(&philo->data->stop_mut);
		if (philo->data->stop == 1)
			return (pthread_mutex_unlock(&philo->data->stop_mut), NULL);
		pthread_mutex_unlock(&philo->data->stop_mut);
		usleep(1000); //-------------------
	}
	return (NULL);
}
