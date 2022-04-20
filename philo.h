/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salaverd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 14:26:56 by salaverd          #+#    #+#             */
/*   Updated: 2022/04/19 20:31:21 by salaverd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include "philo.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <string.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				id;
	int				eat_num;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_t		thread;
	pthread_mutex_t	mutex;
	struct s_utils	*utils;
	struct timeval	last_time_to_eat;
}				t_philo;

typedef struct s_utils
{
	int				number_of_philosophers;
	int				num_of_eat_finish_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_must_eat;
	int				finish;
	pthread_mutex_t	finish_mutex;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	struct timeval	create_time;
}				t_utils;

int		init(t_utils *util, int argc, char **argv);
int		ft_error(char *str);
int		ft_atoi(const char *str);
int		ft_malloc(void *dst, size_t size);
void    *start(void *argv);
void    *show(void *argv);
void    *show_each_must_eat(void *argv);
void	print_res(t_philo *philo, char *str);
long long   convert_time(struct timeval now);
void	pick_fork(t_philo *philo);
void    eat(t_philo *philo);
void	sleeping(t_philo *philo);
void	think(t_philo *philo);
#endif
