/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_nd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgavairo <jgavairo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 15:27:14 by jgavairo          #+#    #+#             */
/*   Updated: 2024/07/16 14:48:35 by jgavairo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_usleep_check(t_philosopher *philo, int time)
{
	long	start_time;
	long	time_to_wait;

	start_time = get_timestamp();
	while ((get_timestamp() - start_time) < time)
	{
		if (death_checker(philo) == -1)
			return ;
		time_to_wait = ((time - (get_timestamp() - start_time)) * 1000) / 2;
		if (time_to_wait > 150)
			usleep(150);
		else
			usleep(time_to_wait);
	}
}

void	program_stopper(t_philosopher *philo, t_data *data)
{
	(void)philo;
	pthread_mutex_lock(&data->stop_mut);
	data->stop = 1;
	pthread_mutex_unlock(&data->stop_mut);
	ft_clean(data, &philo);
}

int	parser(t_data *data)
{
	if (data->number_of_philosophers > 200)
		return (p_error("Error: invalid number of philosophers\n"), -1);
	if (data->number_of_philosophers <= 0)
		return (p_error("Error: invalid number of philosophers\n"), -1);
	if (data->time_to_die >= 2147483647 || data->time_to_die < 0)
		return (p_error("Error: invalid time to die\n"), -1);
	if (data->time_to_eat >= 2147483647 || data->time_to_eat < 0)
		return (p_error("Error: invalid time to eat\n"), -1);
	if (data->time_to_sleep >= 2147483647 || data->time_to_sleep < 0)
		return (p_error("Error: invalid time to sleep\n"), -1);
	if (data->number_of_meals >= 2147483647)
		return (p_error("Error: invalid number of meals\n"), -1);
	return (0);
}

void	p_error(char *str)
{
	write (2, str, ft_strlen(str));
}

void	ft_clean(t_data *data, t_philosopher **philo)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_join((*philo)[i].thread, NULL);
		i++;
	}
	i = 0;
	while (i < data->number_of_philosophers)
	{
		if ((*philo)[i].left_fork)
		{
			pthread_mutex_destroy((*philo)[i].left_fork);
			free((*philo)[i].left_fork);
		}
		i++;
	}
	free(*philo);
	*philo = NULL;
}
