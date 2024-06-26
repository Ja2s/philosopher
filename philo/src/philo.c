/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgavairo <jgavairo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 16:20:14 by jgavairo          #+#    #+#             */
/*   Updated: 2024/06/28 14:38:05 by jgavairo         ###   ########.fr       */
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
		//printf ("PHILO |%d| : OK\n", (*philo)[i].id);
		i++;
	}
	i = 0;
	while(i < data->number_of_philosophers)
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

int	main(int argc, char **argv)
{
	t_data			data;
	t_philosopher	*philo;
	int				i;

	i = 0;
	data_init(argc, argv, &data);
	init_philosophers(&data, &philo);
	while (1)
	{
		while (i < data.number_of_philosophers)
		{
			if (check_nb_meals(&data, &philo[i]) == -1)
				return (ft_clean(&data, &philo), -1);	
			if (check_death(&philo[i], &data) == -1)
				return (ft_clean(&data, &philo), -1);
			i++;
		}
		if (data.max_meal == 1)
		{
			pthread_mutex_lock(&data.stop_mut);
			data.stop = 1;
			pthread_mutex_unlock(&data.stop_mut);
			return (ft_clean(&data, &philo), -1);
		}
		i = 0;
		usleep(5);
		usleep(1000); //-------------------
	}
	return (ft_clean(&data, &philo), 0);
}
