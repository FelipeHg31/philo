/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-her <juan-her@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 15:55:34 by juan-her          #+#    #+#             */
/*   Updated: 2026/02/07 23:43:44 by juan-her         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	ft_atol(char *str)
{
	unsigned long	value;
	int				i;

	value = 0;
	i = 0;
	if (str[i] == '+')
		i++;
	if (str[i] == '-' || str[i] == '0')
		return (0);
	while (str[i] >= '0' && str[i] <= '9')
	{
		value = (value * 10) + (str[i] - '0');
		i++;
	}
	if (str[i] != '\0')
		return (0);
	if (value > 2147483647)
		return (0);
	return (value);
}

unsigned long	ft_get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_print_message(t_philo *philo, char *message)
{
	unsigned long	time;

	pthread_mutex_lock(&philo->general->write);
	if (!ft_is_dead(philo->general))
	{
		time = ft_get_time() - philo->general->time;
		printf("%lu ms %d %s\n", time, philo->id, message);
	}
	pthread_mutex_unlock(&philo->general->write);
}

void	ft_usleep(unsigned long time, t_general *gen)
{
	unsigned long	start;

	start = ft_get_time();
	while (!ft_is_dead(gen))
	{
		if (ft_get_time() - start >= time)
			break ;
		usleep(50);
	}
}
