/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-her <juan-her@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 03:50:06 by juan-her          #+#    #+#             */
/*   Updated: 2025/12/14 21:54:01 by juan-her         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


static int ft_set_nums2(t_general *general, char **ag)
{
    unsigned long num;

    num = ft_atol(ag[4]);
    if (num)
        general->time_sleep = num;
    else
        return (0);
    if (!ag[5])
    {
        general->meals_needed = 0;
        return (1);}
    num = ft_atol(ag[5]);
    if (num)
        general->meals_needed = num;
    else
        return (0);
    return (1);
}

static int ft_set_nums(t_general *general, char **ag)
{
    unsigned long num;

    num = ft_atol(ag[1]);
    if (num)
        general->count = (int) num;
    else
        return (0);
    num = ft_atol(ag[2]);
    if (num)
        general->time_die = num;
    else
        return (0);
    num = ft_atol(ag[3]);
    if (num)
        general->time_eat = num;
    else
        return (0);
    return (ft_set_nums2(general, ag));
}

static void ft_init_philo(t_general *general)
{
    int i;
    unsigned long calculate;

    i = 0;
    while (i < general->count)
    {
        general->philos[i].id = i + 1;
        general->philos[i].general = general;
        general->philos[i].count_meals = 0;
        general->philos[i].time_meal = ft_get_time();
        general->philos[i].right_fork = i;
        calculate = (i + 1) % general->count;
        general->philos[i].left_fork = calculate;
        general->philos[i].state = 0;
        i++;
    }
}

int ft_init_data(t_general *general, char **ag)
{
    int i;
    
    i = 0;
    if (!ft_set_nums(general, ag))
        return (0);
    general->forks = malloc(sizeof(pthread_mutex_t) * general->count);
    if (!general->forks)
        return (0);
    while (i < general->count)
    {
        pthread_mutex_init(&(general)->forks[i], NULL);
        i++;
    }
    general->philos = malloc(sizeof(t_philo) * general->count);
    if (!general->philos)
        return (0);
    general->deaths = 0;
    ft_init_philo(general);
    return (1);
}
