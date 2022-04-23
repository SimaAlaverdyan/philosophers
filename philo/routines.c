/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salaverd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 16:39:24 by salaverd          #+#    #+#             */
/*   Updated: 2022/04/23 16:39:34 by salaverd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*routine(void *vphilo)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)vphilo;
	philo->last_meal = get_time();
	philo->threshold = philo->last_meal + philo->instance->ttdie;
	while (1)
	{
		if (take_forks(philo) || eat(philo) || release_forks(philo))
			break ;
	}
	return (NULL);
}
