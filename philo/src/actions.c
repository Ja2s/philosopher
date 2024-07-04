/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgavairo <jgavairo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:24:37 by jgavairo          #+#    #+#             */
/*   Updated: 2024/07/04 13:58:22 by jgavairo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	eating(t_philosopher *philo)
{
	long	time;

	if (write_status(philo, "is eating") == -1)
		return (-1);
	time = (philo->data->time_to_eat);
	if (death_checker(philo) == -1)
		return (-1);
	pthread_mutex_lock(&philo->data->meals);
	philo->meals_eaten++;
	philo->last_meal = get_timestamp();
	pthread_mutex_unlock(&philo->data->meals);
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

int	eat_helper(t_philosopher *philo, int choice)
{
	if (choice == 1)
	{	
		pthread_mutex_lock(philo->left_fork);
		if (philo->left_fork_bool == true)
		{
			pthread_mutex_unlock(philo->left_fork);
			usleep(150);
			return (0);
		}
	}
	else if (choice == 2)
	{
		if (*philo->right_fork_bool == true)
		{
			pthread_mutex_unlock(philo->right_fork);
			usleep(150);
			return (0) ;
		}
	}
	return (1);
}

int	philo_eat(t_philosopher *philo)
{
	while (usleep (150), 1)
	{
		if (death_checker(philo) == -1)
			return (-1);
		if (eat_helper(philo, 1) == 0)
			continue ;
		philo->left_fork_bool = true;
		pthread_mutex_unlock(philo->left_fork);
		if (write_status(philo, "has take a fork") == -1)
			return (-1);
		while (usleep (150), 1)
		{
			if (death_checker(philo) == -1)
				return (-1);
			pthread_mutex_lock(philo->right_fork);
			if (eat_helper(philo, 2) == 0)
				continue ;
			*philo->right_fork_bool = true;
			pthread_mutex_unlock(philo->right_fork);
			if (write_status(philo, "has take a fork") == -1)
				return (-1);
			return (eating(philo), 0);
		}
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

void	*philo_routine(void *arg)
{
	t_philosopher	*philo;
	long			time_eat;

	philo = (t_philosopher *)arg;
	time_eat = (philo->data->time_to_eat / 2) * 1000;
	waiting_room(philo);
	if (philo->id % 2 == 0)
		usleep(time_eat);
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
		usleep(150);
	}
	return (NULL);
}
