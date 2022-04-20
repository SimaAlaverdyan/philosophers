#include "philo.h"

void	pick_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	print_res(philo, "has taken a fork");
	pthread_mutex_lock(philo->left_fork);
	print_res(philo, "has taken a fork");
}

void    eat(t_philo *philo)
{
	long long	ms;

	pthread_mutex_lock(&philo->mutex);
	gettimeofday(&philo->last_time_to_eat, NULL);
	ms = convert_time(philo->last_time_to_eat) - \
		convert_time(philo->utils->create_time);
	pthread_mutex_lock(&philo->utils->finish_mutex);
	if (!philo->utils->finish)
		printf("%lld\t%d\t %s\n", ms, philo->id + 1, "is eating");
	philo->eat_num += 1;
	if (philo->eat_num == philo->utils->number_of_must_eat)
		philo->utils->num_of_eat_finish_philo += 1;
	pthread_mutex_unlock(&philo->utils->finish_mutex);
	usleep(philo->utils->time_to_eat * 1000);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(&philo->mutex);
}

void	sleeping(t_philo *philo)
{
	print_res(philo, "is sleeping");
	usleep(philo->utils->time_to_sleep * 1000);
}

void	think(t_philo *philo)
{
	print_res(philo, "is thinking");
}