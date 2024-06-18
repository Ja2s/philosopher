/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgavairo <jgavairo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 16:20:14 by jgavairo          #+#    #+#             */
/*   Updated: 2024/06/18 15:26:45 by jgavairo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

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
				return (-1);
			if (check_death(&philo[i], &data) == -1)
				return (-1);
			i++;
		}
		i = 0;
		usleep(100);
	}
	return (0);
}
