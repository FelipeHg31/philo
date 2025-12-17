/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-her <juan-her@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 03:04:12 by juan-her          #+#    #+#             */
/*   Updated: 2025/12/17 21:16:27 by juan-her         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int ft_data(int ac, char **ag, t_general *data)
{
	if (ac < 5 || ac > 6)
	{
		write(2, "Error: Invalid number of arguments", 35);
		return (0);
	}
	if (!ft_init_data(data, ag))
	{
		write(2, "Error: Set data", 16);
		return (0);
	}
	return (1);
}

int	main(int ac, char **ag)
{
	t_general	data;
	int i;

	i = 0;
	if (!ft_data(ac, ag, &data))
		return (1);
	data.time = ft_get_time();
	pthread_mutex_init(&data.write, NULL);
	pthread_mutex_init(&data.die, NULL);
	pthread_mutex_init(&data.meals, NULL);
	while (i < data.count)
	{
		pthread_mutex_init(&data.philos[i].last_meal, NULL);
		pthread_create(&data.philos[i].thread, NULL, ft_philo_routine, &data.philos[i]);
		i++;
	}
	pthread_create(&data.monitoring, NULL, ft_monitoring, &data);
	pthread_join(data.monitoring, NULL);
	i = 0;
	while (i < data.count)
	{
		pthread_join(data.philos[i].thread, NULL);
		i++;
	}
	i = 0;
	while (i < data.count)
	{
		pthread_mutex_destroy(&data.philos[i].last_meal);
		pthread_mutex_destroy(&data.forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data.write);
	pthread_mutex_destroy(&data.die);
	pthread_mutex_destroy(&data.meals);
	free(data.philos);
	free(data.forks);
	data.philos = NULL;
	data.forks = NULL;
	return (0);
}
