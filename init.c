/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salaverd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 15:58:38 by salaverd          #+#    #+#             */
/*   Updated: 2022/04/19 20:23:07 by salaverd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	parse_args(t_utils *utils, int argc, char **argv)
{
	utils->number_of_philosophers = ft_atoi(argv[1]);
	utils->time_to_die = ft_atoi(argv[2]);
	utils->time_to_eat = ft_atoi(argv[3]);
	utils->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		utils->number_of_must_eat = ft_atoi(argv[5]);
}

int	parse_philos(t_utils *utils)
{
	int	i;

	pthread_mutex_init(&utils->finish_mutex, NULL);
	if (ft_malloc(&utils->philos, sizeof(t_philo) * utils->number_of_philosophers) || \
		ft_malloc(&utils->forks, sizeof(pthread_mutex_t) * utils->number_of_philosophers))
		return (ft_error("ERROR: malloc failed\n"));
	i = 0;
	while (i < utils->number_of_philosophers)
	{
		utils->philos[i].id = i;
		pthread_mutex_init(&utils->forks[i], NULL);
		pthread_mutex_init(&utils->philos[i].mutex, NULL);
		if (i == 0)
			utils->philos[i].left_fork = &utils->forks[utils->number_of_philosophers - 1];
		else
			utils->philos[i].left_fork = &utils->forks[i - 1];
		utils->philos[i].right_fork = &utils->forks[i];
		utils->philos[i].utils = utils;
		++i;
	}
	return (0);
}

int	init(t_utils *utils, int argc, char **argv)
{
	parse_args(utils, argc, argv);
	//check
	if (parse_philos(utils))
		return (1);
	return (0);
}
