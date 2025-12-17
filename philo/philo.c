/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-her <juan-her@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 03:04:17 by juan-her          #+#    #+#             */
/*   Updated: 2025/12/15 00:02:33 by juan-her         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void ft_take_forks(t_philo *philo)
{
    int left_fork;
    int right_fork;
    
    left_fork = philo->id;
    right_fork = (philo->id + 1) % philo->general->count;
    if (philo->id % 2 == 0)
    {
        pthread_mutex_lock(&philo->general->forks[left_fork]);
        ft_print_message(philo, "has taken a fork");
        pthread_mutex_lock(&philo->general->forks[right_fork]);
    }
    else
    {
        pthread_mutex_lock(&philo->general->forks[right_fork]);
        ft_print_message(philo, "has taken a fork");
        pthread_mutex_lock(&philo->general->forks[left_fork]);
    }
}

static void ft_drop_forks(t_philo *philo)
{
    int left_fork;
    int right_fork;
    
    left_fork = philo->id;
    right_fork = (philo->id + 1) % philo->general->count;
    pthread_mutex_unlock(&philo->general->forks[left_fork]);
    pthread_mutex_unlock(&philo->general->forks[right_fork]);
}

static int ft_is_dead(t_general *gen)
{
    int dead;
    pthread_mutex_lock(&gen->die);
    dead = gen->deaths;
    pthread_mutex_unlock(&gen->die);
    return (dead);
}

void *ft_philo_routine(void *philo_data)
{
    t_philo *philo;

    philo = (t_philo *)philo_data;
    if (philo->id % 2 == 0)
        usleep(1500);
    while (!ft_is_dead(philo->general))
    {
        ft_print_message(philo, "is thiking");
        ft_take_forks(philo);
        ft_print_message(philo, "is eating");
        pthread_mutex_lock(&philo->last_meal);
        philo->time_meal = ft_get_time();
        pthread_mutex_unlock(&philo->last_meal);
        usleep(philo->general->time_eat * 1000);
        ft_drop_forks(philo);
        ft_print_message(philo, "is sleeping");
        usleep(philo->general->time_sleep * 1000);
    }
    return (NULL);
}

void *ft_monitoring(void *data)
{
    t_general *gen;
    int i;

    gen = (t_general *) data;
    i = -1;
    while (1)
    {
        while (++i < gen->count)
        {
            pthread_mutex_lock(&gen->philos[i].last_meal);
            if ((ft_get_time() - gen->philos[i].time_meal) > gen->time_die)
            {
                pthread_mutex_unlock(&gen->philos->last_meal);
                pthread_mutex_lock(&gen->die);
                gen->deaths += 1;
                pthread_mutex_unlock(&gen->die);
                pthread_mutex_lock(&gen->write);
                ft_print_message(&gen->philos[i], "is death");
                pthread_mutex_unlock(&gen->write);
                return (NULL);
            }
            pthread_mutex_unlock(&gen->philos[i].last_meal);
        }
    }
    return (NULL);    
}