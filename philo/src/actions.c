/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgavairo <jgavairo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:24:37 by jgavairo          #+#    #+#             */
/*   Updated: 2024/06/27 15:05:16 by jgavairo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	take_left_fork(t_philosopher *philo)
{
	if (death_checker(philo) == -1)
		return (-1);
	pthread_mutex_lock(philo->left_fork);
	if (philo->left_fork_bool == false)
	{
		philo->left_fork_bool = true;
		pthread_mutex_unlock(philo->left_fork);
		if (write_status(philo, "has taken a fork") == -1)
				return (-1);
		return (0);
	}
	else
	{
		pthread_mutex_unlock(philo->left_fork);
		return (-1);
	}
	//usleep(1000); //-------------------
}

int	eating(t_philosopher *philo)
{
	long	time;

	if (death_checker(philo) == -1)
		return (-1);
	pthread_mutex_lock(&philo->data->eat_time_mut);
	time = (philo->data->time_to_eat);
	pthread_mutex_unlock(&philo->data->eat_time_mut);
	if (death_checker(philo) == -1)
		return (-1);
	//pthread_mutex_lock(&philo->data->meals);
	pthread_mutex_lock(&philo->data->eat_time_mut);
	philo->meals_eaten++;
	philo->last_meal = get_timestamp();
	pthread_mutex_unlock(&philo->data->eat_time_mut);
	//pthread_mutex_unlock(&philo->data->meals);
	if (death_checker(philo) == -1)
		return (-1);
	ft_usleep_check(philo, time);
	if (death_checker(philo) == -1)
		return (-1);
	pthread_mutex_lock(philo->left_fork);
	philo->left_fork_bool = false;
	pthread_mutex_unlock(philo->left_fork);
	if (death_checker(philo) == -1)
		return (-1);
	pthread_mutex_lock(philo->right_fork);
	*philo->right_fork_bool = false;
	pthread_mutex_unlock(philo->right_fork);
	return (0);
}

int	philo_eat(t_philosopher *philo)
{
	while (1)
	{
		if (death_checker(philo) == -1)
			return (-1);

		if (take_left_fork(philo) != 0)
		{
			if (death_checker(philo) == -1)
				return (-1);
			usleep(5);
			continue;
		}

		while (1)
		{	
			if (death_checker(philo) == -1)
				return (-1);
			pthread_mutex_lock(philo->right_fork);
			if (*(philo->right_fork_bool) == true)
			{
				pthread_mutex_unlock(philo->right_fork);
				usleep(5);
				continue;
			}
			*(philo->right_fork_bool) = true;
			pthread_mutex_unlock(philo->right_fork);
			if (write_status(philo, "has taken a fork") == -1)
				return (-1);
			if (write_status(philo, "is eating") == -1)
				return (-1);
			if (eating(philo) == -1)
				return (-1);
			return (0);
		}
		//usleep(1000); //-------------------
	}
	return (0);
}

int	philo_sleep(t_philosopher *philo)
{
	if (write_status(philo, "is sleeping") == -1)
		return (-1);
	if (death_checker(philo) == -1)
		return (-1);
	ft_usleep_check(philo, philo->data->time_to_sleep);
	//usleep(philo->data->time_to_sleep * 1000);
	if (death_checker(philo) == -1)
		return (-1);
	if (write_status(philo, "is thinking") == -1)
		return (-1);
	// ft_usleep_check(philo, 1);
	//usleep(philo->data->time_to_die - (get_timestamp() - philo->last_meal) - 1000);
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
			philo->last_meal = get_timestamp();
			break ;
		}
		pthread_mutex_unlock(&philo->data->start_mut);
		//ft_usleep(1);
	}
	if (philo->id % 2 == 0)
		usleep(philo->data->time_to_eat / 4 * 1000);
	while (1)
	{
		if (philo_eat(philo) == -1)
			return (NULL);
		if (death_checker(philo) == -1)
			return (NULL);
		if (philo_sleep(philo) == -1)
			return (NULL);
		if (death_checker(philo) == -1)
			return (NULL);
		//usleep(1000); //-------------------
	}
	return (NULL);
}
