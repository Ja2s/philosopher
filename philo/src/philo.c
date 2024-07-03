/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgavairo <jgavairo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 13:31:23 by jgavairo          #+#    #+#             */
/*   Updated: 2024/07/03 16:45:30 by jgavairo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

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

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	p_error(char *str)
{
	write (2, str, ft_strlen(str));
}

int	parser(t_data *data)
{
	if (data->number_of_philosophers > 200)
		return (p_error("Error: too many philosophers\n"), -1);
	if (data->number_of_philosophers == 0)
		return (p_error("Error: too few philosophers\n"), -1);
	if (data->time_to_die > 2147483648)
		return (p_error("Error: invalid time to die\n"), -1);
	if (data->time_to_eat > 2147483648)
		return (p_error("Error: invalid time to eat\n"), -1);
	if (data->time_to_sleep > 2147483648)
		return (p_error("Error: invalid time to sleep\n"), -1);
	if (data->number_of_meals >= 2147483647)
		return (p_error("Error: too many meals\n"), -1);
	return (0);
}

int	end_checker(t_data *data, t_philosopher *philo, int i)
{
	if (check_nb_meals(data, &philo[i]) == -1)
		return (-1);
	if (check_death(&philo[i], data) == -1)
		return (-1);
	return (0);
}

void	program_stopper(t_philosopher *philo, t_data *data)
{
	(void)philo;
	pthread_mutex_lock(&data->stop_mut);
	data->stop = 1;
	pthread_mutex_unlock(&data->stop_mut);
	ft_clean(data, &philo);
}

int	main(int argc, char **argv)
{
	t_data			data;
	t_philosopher	*philo;
	int				i;

	if (data_init(argc, argv, &data) == -1)
		return (-1);
	if (parser(&data) == -1)
		return (-1);
	init_philosophers(&data, &philo);
	while (1)
	{
		i = 0;
		while (i < data.number_of_philosophers)
		{
			if (end_checker(&data, philo, i) == -1)
				return (ft_clean(&data, &philo), -1);
			i++;
		}
		if (data.max_meal == 1)
			return (program_stopper(philo, &data), -1);
		usleep(5);
	}
	return (ft_clean(&data, &philo), 0);
}
