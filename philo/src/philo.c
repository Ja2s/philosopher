/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgavairo <jgavairo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 13:31:23 by jgavairo          #+#    #+#             */
/*   Updated: 2024/07/16 15:03:25 by jgavairo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

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
			if (data.max_meal == 0)
				break ;
			i++;
		}
		if (data.max_meal == 1)
			return (program_stopper(philo, &data), -1);
		usleep(5);
	}
	return (ft_clean(&data, &philo), 0);
}
