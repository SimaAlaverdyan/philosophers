#include "philo.h"

long long   convert_time(struct timeval now)
{
	long long		ms;

	ms = now.tv_sec * 1000;
	ms += now.tv_usec / 1000;
	return (ms);
}

void	print_res(t_philo *philo, char *str)
{
	long long		ms;
	struct timeval	now;

	pthread_mutex_lock(&philo->utils->finish_mutex);
	gettimeofday(&now, NULL);
	ms = convert_time(now) - convert_time(philo->utils->create_time);
	if (!philo->utils->finish)
		printf("%lld\t%d\t %s\n", ms, philo->id + 1, str);
	pthread_mutex_unlock(&philo->utils->finish_mutex);
}

void    *start(void *argv)
{
    t_philo *philo;

    philo = argv;
    if (philo->id % 2 == 0)
        usleep(philo->utils->time_to_eat * 1000);
    while (!philo->utils->finish)
    {
        pick_fork(philo);
        eat(philo);
        sleeping(philo);
        think(philo);
    }
    return (0);
}

void    *show(void *argv)
{
    t_philo			*philo;
	struct timeval	now;
	long long		ms;

	philo = argv;
	while (!philo->utils->finish)
	{
		pthread_mutex_lock(&philo->mutex);
		pthread_mutex_lock(&philo->utils->finish_mutex);
		gettimeofday(&now, NULL);
		ms = convert_time(now) - convert_time(philo->last_time_to_eat);
		gettimeofday(&now, NULL);
		if (ms >= philo->utils->time_to_die && philo->utils->finish == 0)
		{
			printf("%lld\t%d\t %s\n", \
				convert_time(now) - convert_time(philo->utils->create_time), \
				philo->id + 1, "died");
			philo->utils->finish = 1;
		}
		pthread_mutex_unlock(&philo->utils->finish_mutex);
		pthread_mutex_unlock(&philo->mutex);
	}
	return (NULL);
}

void    *show_each_must_eat(void *argv)
{
    t_utils *utils;

	utils = argv;
	while (!utils->finish)
	{
		pthread_mutex_lock(&utils->finish_mutex);
		if (utils->num_of_eat_finish_philo == utils->number_of_philosophers)
			utils->finish = 1;
		pthread_mutex_unlock(&utils->finish_mutex);
	}
	return (NULL);
}