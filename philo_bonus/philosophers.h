/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salaverd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 18:14:25 by salaverd          #+#    #+#             */
/*   Updated: 2022/04/23 18:15:43 by salaverd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <semaphore.h>
# include <sys/time.h>
# include <signal.h>

# define WRONG_ARGUMENT -1
# define TOO_MANY_ARGUMENTS -2
# define MALLOC_ERROR -3
# define PTHREAD_ERROR -4

struct	s_main;

typedef enum e_action
{
	TAKING_FORK,
	EATING,
	SLEEPING,
	THINKING,
	DIED,
	OVER,
}				t_action;

typedef struct s_philosopher
{
	size_t				position;
	size_t				meals;
	size_t				eating;
	size_t				last_meal;
	struct timeval		create_time;
	size_t				threshold;
	pid_t				pid;
	struct s_main		*instance;
}				t_philosopher;

typedef struct s_main
{
	size_t			amount;
	size_t			tteat;
	size_t			ttdie;
	size_t			ttsleep;
	size_t			meals;
	size_t			finished;
	t_philosopher	*philosophers;
	sem_t			*write_sem;
	sem_t			*frks_sem;
	sem_t			*die_sem;
	pid_t			pid;
}				t_main;

int			ft_atoi(const char *string, size_t *dst);
void		ft_msg(t_philosopher *philo, size_t timestamp, int action);
int			ft_log(int error);
size_t		get_time(void);
void		*routine(void *vphilo);
int			start(t_main *instance);
int			take_forks(t_philosopher *philo);
int			eat(t_philosopher *philo);
int			release_forks(t_philosopher *philo);
void		ft_usleep(size_t ms);
void		*wait_children(void *vinstance);
long long	time_to_ms(struct timeval now);
#endif
