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

int var = 0;
pthread_mutex_t mutex;

void*	action()
{
	pthread_mutex_lock(&mutex);
	for (int i = 0; i < 100000; i++)
		var++;
	pthread_mutex_unlock(&mutex);
	return (0);
}
int	main(void)
{
	pthread_t t1, t2;

	pthread_mutex_init(&mutex, NULL);
	if (pthread_create(&t1, NULL, &action, NULL) != 0)
		return (1);
	if (pthread_create(&t2, NULL, &action, NULL) != 0)
		return (2);
	if (pthread_join(t1, NULL) != 0)
		return (3);
	if (pthread_join(t2, NULL) != 0)
		return (4);
	printf("%d\n", var);
	pthread_mutex_destroy(&mutex);
	return (0);
}
