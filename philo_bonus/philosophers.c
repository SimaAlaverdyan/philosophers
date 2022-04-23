/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salaverd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 18:15:21 by salaverd          #+#    #+#             */
/*   Updated: 2022/04/23 18:15:31 by salaverd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	start(t_main *instance)
{
	size_t		i;
	pthread_t	tid;

	i = 0;
	while (i < instance->amount)
	{
		instance->philosophers[i].pid = fork();
		if (!instance->philosophers[i].pid)
		{
			routine(&instance->philosophers[i]);
			exit(0);
		}
		if (instance->amount % 2)
			ft_usleep(500);
		i++;
	}
	pthread_create(&tid, NULL, wait_children, (void *)instance);
	pthread_detach(tid);
	return (0);
}

int	is_dead(t_philosopher *philo)
{
	if (!philo->eating && get_time() > philo->threshold)
	{
		ft_msg(philo, get_time() - time_to_ms(philo->create_time), DIED);
		sem_post(philo->instance->die_sem);
		return (1);
	}
	return (0);
}

int	take_forks(t_philosopher *philo)
{
	int		i;

	i = 0;
	while (i < 2)
	{
		if (is_dead(philo))
			return (1);
		if (!(i == 1 && philo->instance->amount == 1))
		{
			sem_wait(philo->instance->frks_sem);
			ft_msg(philo, get_time() - time_to_ms(philo->create_time),
				TAKING_FORK);
			i++;
		}
	}
	return (0);
}

int	release_forks(t_philosopher *philo)
{
	sem_post(philo->instance->frks_sem);
	sem_post(philo->instance->frks_sem);
	ft_msg(philo, philo->last_meal + philo->instance->tteat
		- time_to_ms(philo->create_time), SLEEPING);
	ft_usleep(philo->instance->ttsleep);
	if (is_dead(philo))
		return (1);
	ft_msg(philo, philo->last_meal + philo->instance->tteat
		+ philo->instance->ttsleep - time_to_ms(philo->create_time), THINKING);
	return (0);
}

int	eat(t_philosopher *philo)
{
	philo->eating = 1;
	philo->last_meal = get_time();
	ft_msg(philo, philo->last_meal - time_to_ms(philo->create_time), EATING);
	ft_usleep(philo->instance->tteat);
	philo->threshold = philo->last_meal + philo->instance->ttdie;
	philo->eating = 0;
	philo->meals += 1;
	if (philo->instance->meals > 0 && philo->meals >= philo->instance->meals)
	{
		sem_post(philo->instance->frks_sem);
		sem_post(philo->instance->frks_sem);
		return (1);
	}
	return (0);
}
