/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salaverd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 18:16:14 by salaverd          #+#    #+#             */
/*   Updated: 2022/04/23 18:16:25 by salaverd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi(const char *string, size_t *dst)
{
	int	i;

	i = 0;
	if (string[i] == '\0')
		return (1);
	*dst = 0;
	while (string[i] && string[i] >= '0' && string[i] <= '9')
	{
		*dst = *dst * 10 + (string[i] - '0');
		i++;
	}
	if (string[i] != '\0')
		return (1);
	return (0);
}

size_t	get_time(void)
{
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

long long	time_to_ms(struct timeval now)
{
	long long		ms;

	ms = now.tv_sec * 1000;
	ms += now.tv_usec / 1000;
	return (ms);
}

void	ft_usleep(size_t ms)
{
	size_t	end;

	end = get_time() + ms;
	while (get_time() < end)
		usleep(ms / 1000);
}

void	*wait_children(void *vinstance)
{
	size_t	i;
	t_main	*instance;

	i = -1;
	instance = (t_main *)vinstance;
	while (++i < instance->amount)
		waitpid(instance->philosophers[i].pid, NULL, 0);
	exit(0);
}
