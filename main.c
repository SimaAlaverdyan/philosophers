/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salaverd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 14:55:44 by salaverd          #+#    #+#             */
/*   Updated: 2022/04/19 20:31:24 by salaverd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philos(t_utils *utils)
{
	int			i;
	pthread_t	thread;

	gettimeofday(&utils->create_time, NULL);
	i = 0;
	while (i < utils->number_of_philosophers)
	{
		utils->philos[i].last_time_to_eat = utils->create_time;
		pthread_create(&utils->philos[i].thread, NULL, start, &utils->philos[i]);
		pthread_create(&thread, NULL, show, &utils->philos[i]);
		pthread_detach(thread);
		i++;
	}
	if (utils->number_of_must_eat != 0)
	{
		pthread_create(&thread, NULL, show_each_must_eat, utils);
		pthread_detach(thread);
	}	
}

void	free_and_join(t_utils *utils)
{
	int	i;

	i = 0;
	while (i < utils->number_of_philosophers)
	{
		pthread_join(utils->philos[i].thread, NULL);
		pthread_mutex_destroy(&utils->philos[i++].mutex);
	}
	free(utils->philos);
	i = 0;
	while (i < utils->number_of_philosophers)
		pthread_mutex_destroy(&utils->forks[i++]);
	free(utils->forks);
}

int	main(int argc, char **argv)
{
	t_utils utils;
	memset(&utils, 0, sizeof(utils));
	if (argc != 5 && argc != 6)
		return (ft_error("Wrong number of argumnet!"));
	if (init(&utils, argc, argv))
		return (1);
	init_philos(&utils);
	free_and_join(&utils);
	return (0);
}
