/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salaverd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 16:36:53 by salaverd          #+#    #+#             */
/*   Updated: 2022/04/23 16:38:14 by salaverd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	start(t_main *instance)
{
	size_t		i;
	pthread_t	tid;

	i = 0;
	pthread_mutex_lock(&instance->die_mutex);
	while (i < instance->amount)
	{
		if (pthread_create(&tid, NULL, &routine,
				(void *)&instance->philosophers[i]))
			return (ft_log(PTHREAD_ERROR));
		pthread_detach(tid);
		if (instance->amount % 2)
			ft_usleep(500);
		i++;
	}
	return (0);
}

int	is_dead(t_philosopher *philo)
{
	if (!philo->eating && get_time() > philo->threshold)
	{
		ft_msg(philo, get_time() - time_to_ms(philo->create_time) - 1, DIED);
		pthread_mutex_lock(&philo->instance->write_mutex);
		pthread_mutex_unlock(&philo->instance->die_mutex);
		return (1);
	}
	return (0);
}

int	take_forks(t_philosopher *philo)
{
	int		i;
	size_t	fork;

	i = 0;
	while (i < 2)
	{
		if (is_dead(philo))
			return (1);
		if (i == 0)
			fork = philo->l_fork;
		else
			fork = philo->r_fork;
		pthread_mutex_lock(&philo->instance->frks_mutexes[fork]);
		if (!philo->instance->forks[fork])
		{
			ft_msg(philo, get_time() - time_to_ms(philo->create_time),
				TAKING_FORK);
			philo->instance->forks[fork] = 1;
			i++;
		}
		pthread_mutex_unlock(&philo->instance->frks_mutexes[fork]);
	}
	return (0);
}

int	release_forks(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->instance->frks_mutexes[philo->l_fork]);
	philo->instance->forks[philo->l_fork] = 0;
	pthread_mutex_unlock(&philo->instance->frks_mutexes[philo->l_fork]);
	pthread_mutex_lock(&philo->instance->frks_mutexes[philo->r_fork]);
	philo->instance->forks[philo->r_fork] = 0;
	pthread_mutex_unlock(&philo->instance->frks_mutexes[philo->r_fork]);
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
		pthread_mutex_lock(&philo->instance->frks_mutexes[philo->l_fork]);
		philo->instance->forks[philo->l_fork] = 0;
		pthread_mutex_unlock(&philo->instance->frks_mutexes[philo->l_fork]);
		pthread_mutex_lock(&philo->instance->frks_mutexes[philo->r_fork]);
		philo->instance->forks[philo->r_fork] = 0;
		pthread_mutex_unlock(&philo->instance->frks_mutexes[philo->r_fork]);
		philo->instance->finished++;
		if (philo->instance->finished >= philo->instance->amount)
		{
			pthread_mutex_lock(&philo->instance->write_mutex);
			pthread_mutex_unlock(&philo->instance->die_mutex);
		}
		return (1);
	}
	return (0);
}
