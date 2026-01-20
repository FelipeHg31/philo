/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-her <juan-her@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 03:04:59 by juan-her          #+#    #+#             */
/*   Updated: 2026/01/20 18:16:15 by juan-her         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_general	t_general;
typedef struct s_philo		t_philo;

typedef struct s_general
{
	int				count;
	int				meals_needed;
	int				deaths;
	unsigned long	time_eat;
	unsigned long	time;
	unsigned long	time_sleep;
	unsigned long	time_die;
	t_philo			*philos;
	pthread_t		monitoring;
	pthread_mutex_t	die;
	pthread_mutex_t	meals;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write;
}	t_general;

typedef struct s_philo
{
	int				id;
	int				state;
	unsigned long	time_meal;
	int				count_meals;
	int				left_fork;
	int				right_fork;
	pthread_t		thread;
	pthread_mutex_t	last_meal;
	t_general		*general;
}	t_philo;

unsigned long	ft_atol(char *str);
unsigned long	ft_get_time(void);
int				ft_init_data(t_general *general, char **ag);
void			ft_print_message(t_philo *philo, char *message);
int				ft_is_dead(t_general *gen);
void			ft_usleep(unsigned long time, t_general *gen);
void			*ft_routine(void *arg);
void			*ft_monitoring(void *data);

#endif