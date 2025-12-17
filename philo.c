/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-her <juan-her@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 03:04:17 by juan-her          #+#    #+#             */
/*   Updated: 2025/12/17 22:07:06 by juan-her         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_is_dead(t_general *gen)
{
	int	dead;

	pthread_mutex_lock(&gen->die);
	dead = gen->deaths;
	pthread_mutex_unlock(&gen->die);
	return (dead);
}

static void	ft_drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->general->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->general->forks[philo->right_fork]);
}

static int	ft_take_forks(t_philo *philo)
{
	if (ft_is_dead(philo->general))
		return (0);
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->general->forks[philo->left_fork]);
		if (ft_is_dead(philo->general))
		{
			pthread_mutex_unlock(&philo->general->forks[philo->left_fork]);
			return (0);
		}
		ft_print_message(philo, "has taken a fork");
		pthread_mutex_lock(&philo->general->forks[philo->right_fork]);
	}
	else
	{
		pthread_mutex_lock(&philo->general->forks[philo->right_fork]);
		if (ft_is_dead(philo->general))
		{
			pthread_mutex_unlock(&philo->general->forks[philo->right_fork]);
			return (0);
		}
		ft_print_message(philo, "has taken a fork");
		pthread_mutex_lock(&philo->general->forks[philo->left_fork]);
	}
	ft_print_message(philo, "has taken a fork");
	return (1);
}

void	*ft_philo_routine(void *philo_data)
{
	t_philo	*philo;

	philo = (t_philo *)philo_data;
	if (philo->general->count == 1)
	{
		ft_print_message(philo, "has taken a fork");
		ft_usleep(philo->general->time_die, philo->general);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		usleep(500);
	while (!ft_is_dead(philo->general))
	{
		ft_print_message(philo, "is thiking");
		if (!ft_take_forks(philo))
			break ;
		pthread_mutex_lock(&philo->last_meal);
		philo->time_meal = ft_get_time();
		philo->count_meals++;
		pthread_mutex_unlock(&philo->last_meal);
		ft_print_message(philo, "is eating");
		ft_usleep(philo->general->time_eat, philo->general);
		ft_drop_forks(philo);
		ft_print_message(philo, "is sleeping");
		ft_usleep(philo->general->time_sleep, philo->general);
	}
	return (NULL);
}

static int	ft_count_meals(t_general *gen)
{
	int	i;

	if (!gen->meals_needed)
		return (0);

	pthread_mutex_lock(&gen->meals);
	i = 0;
	while (i < gen->count)
	{
		if (gen->philos[i].count_meals < gen->meals_needed)
		{
			pthread_mutex_unlock(&gen->meals);
			return (0);
		}
		i++;
	}
	pthread_mutex_unlock(&gen->meals);
	return (1);
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
				ft_print_message(&gen->philos[i], "died");
				pthread_mutex_lock(&gen->die);
				gen->deaths = 1;
				pthread_mutex_unlock(&gen->die);
				return (NULL);
			}
			pthread_mutex_unlock(&gen->philos[i].last_meal);
			i++;
		}
		if (gen->meals_needed && ft_count_meals(gen))
		{
			ft_print_message(&gen->philos[0], "all eat");
			pthread_mutex_lock(&gen->die);
			gen->deaths = 1;
			pthread_mutex_unlock(&gen->die);
			return (NULL);
		}
		usleep(500);
	}
	return (NULL);
}
