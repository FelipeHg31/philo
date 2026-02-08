/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-her <juan-her@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 18:55:30 by juan-her          #+#    #+#             */
/*   Updated: 2026/02/08 00:35:59 by juan-her         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_count_meals(t_general *gen)
{
	int	i;

	if (!gen->meals_needed)
		return (0);
	i = 0;
	while (i < gen->count)
	{
		pthread_mutex_lock(&gen->philos[i].last_meal);
		if (gen->philos[i].count_meals < gen->meals_needed)
		{
			pthread_mutex_unlock(&gen->philos[i].last_meal);
			return (0);
		}
		pthread_mutex_unlock(&gen->philos[i].last_meal);
		i++;
	}
	return (1);
}

static int	ft_all_eat(t_general *gen)
{
	if (gen->meals_needed && ft_count_meals(gen))
	{
		ft_print_message(&gen->philos[0], "all eat");
		pthread_mutex_lock(&gen->die);
		gen->deaths = 1;
		pthread_mutex_unlock(&gen->die);
		return (1);
	}
	return (0);
}

static void	ft_add_death(t_general *gen, int i)
{
	pthread_mutex_lock(&gen->write);
	pthread_mutex_lock(&gen->die);
	if (!gen->deaths)
	{
		gen->deaths = 1;
		printf("%lu ms %d %s\n",
			ft_get_time() - gen->time, gen->philos[i].id, "died");
	}
	pthread_mutex_unlock(&gen->die);
	pthread_mutex_unlock(&gen->write);
}

void	*ft_monitoring(void *data)
{
	t_general	*gen;
	int			i;

	gen = (t_general *) data;
	while (1)
	{
		i = 0;
		while (i < gen->count)
		{
			pthread_mutex_lock(&gen->philos[i].last_meal);
			if ((ft_get_time() - gen->philos[i].time_meal) > gen->time_die)
			{
				pthread_mutex_unlock(&gen->philos[i].last_meal);
				ft_add_death(gen, i);
				return (NULL);
			}
			pthread_mutex_unlock(&gen->philos[i].last_meal);
			i++;
		}
		if (ft_all_eat(gen))
			return (NULL);
		usleep(50);
	}
	return (NULL);
}
