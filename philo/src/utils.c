/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgavairo <jgavairo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 16:20:08 by jgavairo          #+#    #+#             */
/*   Updated: 2024/06/18 15:43:49 by jgavairo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	write_status(t_philosopher *philo, char *status)
{
	pthread_mutex_lock(philo->data->print);
	printf ("The philosopher %d %s\n", philo->id, status);
	pthread_mutex_unlock(philo->data->print);
}

long	get_timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	check_nb_meals(t_data *data, t_philosopher *philo)
{
	if (data->number_of_meals != -1 && \
	philo->meals_eaten >= data->number_of_meals)
	{
		pthread_mutex_lock(data->print);
		printf("The philosopher %d eats every meal! \U0001F389\n", philo->id);
		return (-1);
	}
	return (0);
}

int	check_death(t_philosopher *philo, t_data *data)
{
	if (get_timestamp() - philo->last_meal > philo->data->time_to_die)
	{
		pthread_mutex_lock(data->print);
		printf("The philosopher %d is dead \U0001F480\n", philo->id);
		return (-1);
	}
	return (0);
}
