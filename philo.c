/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-her <juan-her@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 03:04:17 by juan-her          #+#    #+#             */
/*   Updated: 2026/02/07 23:49:53 by juan-her         ###   ########.fr       */
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
	return (ft_print_message(philo, "has taken a fork"), 1);
}

static int	ft_is_one(t_philo *philo)
{
	if (philo->general->count == 1)
	{
		ft_print_message(philo, "has taken a fork");
		ft_usleep(philo->general->time_die, philo->general);
		return (1);
	}
	return (0);
}

void	*ft_routine(void *philo_data)
{
	t_philo	*philo;

	philo = (t_philo *)philo_data;
	if (ft_is_one(philo))
		return (NULL);
	if (philo->id % 2 == 0)
		ft_usleep(philo->general->time_eat / 2, philo->general);
	while (!ft_is_dead(philo->general))
	{
		ft_print_message(philo, "is thiking");
		if (!ft_take_forks(philo))
			break ;
		pthread_mutex_lock(&philo->last_meal);
		philo->time_meal = ft_get_time();
		philo->count_meals++;
		pthread_mutex_unlock(&philo->last_meal);
		if (ft_is_dead(philo->general))
			break ;
		ft_print_message(philo, "is eating");
		ft_usleep(philo->general->time_eat, philo->general);
		ft_drop_forks(philo);
		ft_print_message(philo, "is sleeping");
		ft_usleep(philo->general->time_sleep, philo->general);
	}
	return (NULL);
}
