/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salaverd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 15:59:08 by salaverd          #+#    #+#             */
/*   Updated: 2022/04/19 20:31:26 by salaverd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int		sign;
	int		dig;
	long	res;
    int     i;

    i = 0;
	sign = 1;
	dig = 0;
	res = 0;

	while (*str == '\n' || *str == '\t' || *str == '\v'
		|| *str == ' ' || *str == '\r' || *str == '\f')
		str++;
	if (*str == '-')
        sign = -1;
	if (*str == '-' || *str == '+')
        str++;
    if (!(*str >= '0' && *str <= '9'))
        return (0);
    while (*str == '0')
        str++;
    while ((*str >= '0') && (*str <= '9'))
    {
        res = res * 10 + (*str - '0');
        dig++;
        str++;
	}
    return (int)(res * sign);
}

int	ft_error(char *str)
{
	char	*s;
	int		i;

	s = str;
	i = 0;
	while (*s++)
		i++;
	write(2, str, i);
	return (0);
}

int	ft_malloc(void *dst, size_t size)
{
	*(void **)dst = malloc(size);
	if (*(void **)dst == NULL)
		return (1);
	memset(*(void **)dst, 0, size);
	return (0);
}
