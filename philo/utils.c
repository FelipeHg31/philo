/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-her <juan-her@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 15:55:34 by juan-her          #+#    #+#             */
/*   Updated: 2025/12/13 17:53:49 by juan-her         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long ft_atol(char *str)
{
    unsigned long value;
    int i;

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

int  ft_len_num(unsigned long n)
{
    int i;
    
    i = 0;
    while (n)
    {
        i++;
        n /= 10;
    }
    return (i);
}

char	*ft_itoa(unsigned long n)
{
	char	*str;
	long	num;
	int		len;

	num = n;
	len = ft_len_num(num);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	len--;
	if (num == 0)
		str[0] = '0';
	while (num > 0)
	{
		str[len] = (num % 10) + '0';
		num /= 10;
		len--;
	}
	return (str);
}

int ft_strlen(char *str)
{
    int i;

    i = 0;
    while (str[i])
        i++;
    return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*join;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	join = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!join)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
		join[j++] = s1[i++];
	i = 0;
	while (s2[i])
		join[j++] = s2[i++];
	join[j] = '\0';
	return (join);
}

