/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgavairo <jgavairo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 16:20:14 by jgavairo          #+#    #+#             */
/*   Updated: 2024/05/30 17:25:58 by jgavairo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

init_philosophers()
{
	
}

start_simulation()
{
	
}

int	main(int argc, char **argv)
{
	t_params 	params;
	int			i;
	
	i = 0;
	if (argc < 5 || argc > 6)
		return(printf("error: invalid argument : (number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_meals])\n"), -1);
	//--------------------stock entrees dans la structure des parametres
	params.number_of_philosophers = atoi(argv[1]);
	params.time_to_die = atol(argv[2]);
	params.time_to_eat = atol(argv[3]);
	params.time_to_sleep = atol(argv[4]);
	if (argv[5])
		params.number_of_meals = atol(argv[5]);
	else
		params.number_of_meals = -1;
	//-------------------
	params.forks = malloc(sizeof(pthread_mutex_t) * params.number_of_philosophers);
	if (!params.forks)
		return (-1);
	//-------------------Initialisation des forks
	while (i < params.number_of_philosophers)
	{
		pthread_mutex_init(&params.forks[i], NULL);
		i++;
	}
	
}