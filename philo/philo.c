/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgavairo <jgavairo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 16:20:14 by jgavairo          #+#    #+#             */
/*   Updated: 2024/06/17 16:37:33 by jgavairo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long get_timestamp() 
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int init_philosophers(t_data *data, t_philosopher **philo)
{
	int	i;
	
	i = 0;
	(*philo) = malloc(sizeof(t_philosopher) * data->number_of_philosophers);
	if (!(*philo))
		return (-1);
	while (i < data->number_of_philosophers)
	{
		(*philo)[i].id = i + 1;
		(*philo)[i].data = data;
		(*philo)[i].meals_eaten = 0;
		(*philo)[i].left_fork_bool = false;
		(*philo)[i].right_fork_bool = (*philo)[(i + 1) % data->number_of_philosophers].left_fork_bool;
		(*philo)[i].last_meal= get_timestamp();
		(*philo)[i].left_fork = malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(philo[i]->left_fork, NULL);
		(*philo)[i].right_fork = ((*philo)[(i + 1) % data->number_of_philosophers].left_fork);
		if (pthread_create(&((*philo)[i].thread), NULL, philo_routine, &((*philo)[i])) != 0)
			return (-1);
		printf("lolllllll\n");
		i++;
	}
	data->start = 1;
	return (0);
}

void philo_eat(t_philosopher *philo)
{
	while (1)
	{
		pthread_mutex_lock(philo->left_fork);
		if (philo->left_fork_bool == false)
		{
			philo->left_fork_bool = true;
			printf ("Le philosopher %d a pris la fourchette de gauche\n", philo->id);
			pthread_mutex_unlock(philo->left_fork);
			break ;
		}
		else
		{
			pthread_mutex_unlock(philo->left_fork);
			usleep(20);
		}
	}
	while (1)
	{
		pthread_mutex_lock(philo->right_fork);
		if (philo->right_fork_bool == false)
		{
			philo->right_fork_bool = true;
			printf ("Le philosopher %d a pris la fourchette de droite\n", philo->id);
			pthread_mutex_unlock(philo->right_fork);
			printf("Le philo %d mange\n", philo->id);
			philo->last_meal = get_timestamp();
			philo->meals_eaten++;
			usleep(philo->data->time_to_sleep * 1000);
			pthread_mutex_lock(philo->left_fork);
			philo->left_fork_bool = false;
			pthread_mutex_unlock(philo->left_fork);
			pthread_mutex_lock(philo->right_fork);
			philo->right_fork_bool = false;
			pthread_mutex_unlock(philo->right_fork);
			break ;
		}
		else
		{
			pthread_mutex_unlock(philo->right_fork);
			usleep(20);
		}
	}
}

void	philo_sleep(t_philosopher *philo)
{	
	printf("le philo %d dort...\n", philo->id);
	usleep(philo->data->time_to_sleep);
	printf("le philo %d pense...\n", philo->id);
}

void	*philo_routine(void *arg)
{
	t_philosopher *philo = (t_philosopher *)arg;
	
	while (1)
	{
		if (philo->data->start == 1)
			break ;
	}
	while (1)
	{
		printf("Le philosopher %d essaie de manger...\n", philo->id);
		philo_eat(philo);
		printf("Le philosopher %d dors...\n", philo->id);
		philo_sleep(philo);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_data 	data;
	t_philosopher *philo;
	int			i;
	
	i = 0;
	if (argc < 5 || argc > 6)
		return(printf("error: invalid argument : (number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_meals])\n"), -1);
	//--------------------stock entrees dans la structure des parametres
	data.start = 0;
	data.number_of_philosophers = atoi(argv[1]);
	data.time_to_die = atol(argv[2]);
	data.time_to_eat = atol(argv[3]);
	data.time_to_sleep = atol(argv[4]);
	if (argv[5])
		data.number_of_meals = atol(argv[5]);
	else
		data.number_of_meals = -1;
	//-------------------
	init_philosophers(&data, &philo);
	if (!philo)
		return (-1);
	
}