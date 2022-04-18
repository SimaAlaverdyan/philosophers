/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salaverd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 14:55:44 by salaverd          #+#    #+#             */
/*   Updated: 2022/04/16 20:02:12 by salaverd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philos(t_utils *utils)
{
	int			i;
	pthread_t	thread;

	gettimeofday(&utils->create_time, NULL);
	i = 0;
	thread = NULL;
	while (i < utils->number_of_philosophers)
	{
		utils->philos[i].last_time_to_eat = utils->create_time;
		//pthread_create(&utils->philos[i].thread, NULL, philo, &utils->philos[i]);
		//pthread_create(&thread, NULL, monitor, &utils->philos[i]);
		//pthread_detach(thread);
		i++;
	}
	if (utils->number_of_must_eat != 0)
	{
		//pthread_create(&thread, NULL, monitor_each_must_eat, utils);
		pthread_detach(thread);
	}	
}

int	main(int argc, char **argv)
{
	t_utils util;

	memset(&util, 0, sizeof(util));
	if (argc != 5 && argc != 6)
		return (ft_error("Wrong number of argumnet!"));
	if (!init(&util, argc, argv))
		return (1);
	init_philos(&util);
	return (0);
}
