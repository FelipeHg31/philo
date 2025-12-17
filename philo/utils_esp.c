/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_esp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-her <juan-her@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 20:16:48 by juan-her          #+#    #+#             */
/*   Updated: 2025/12/15 00:05:12 by juan-her         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	ft_get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void ft_print_message(t_philo *philo, char *message)
{
    char    *msg;
    char    *tmp;
    char    *time;
    char    *id;

    pthread_mutex_lock(&philo->general->write);
    time = ft_itoa(ft_get_time() - philo->general->time);
    id = ft_itoa(philo->id);
    tmp = ft_strjoin(time, " ms ");
    msg = ft_strjoin(tmp, id);
    free(tmp);
    tmp = ft_strjoin(msg, " ");
    free(msg);
    msg =ft_strjoin(tmp, message);
    free(tmp);
    tmp = ft_strjoin(msg, "\n");
    free(msg);
    write(1, tmp, ft_strlen(tmp));
    free(tmp);
    free(time);
    free(id);
    pthread_mutex_unlock(&philo->general->write);
}
