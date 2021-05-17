/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 18:25:08 by aquinoa           #+#    #+#             */
/*   Updated: 2021/05/18 02:41:15 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	err(char *str)
{
	printf("%s", str);
	return (1);
}

long long	ft_atoi(const char *str)
{
	int			n;
	long long	num;

	num = 0;
	n = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			n *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
		num = num * 10 + *str++ - '0';
	return (num * n);
}

unsigned long	what_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	message(t_philo *philo, char *str)
{
	unsigned long	time;

	pthread_mutex_lock(&philo->args->message);
	if (philo->args->death)
	{
		time = what_time() - philo->args->start;
		printf("%lu\t%d\t%s", time, philo->pos, str);
	}
	pthread_mutex_unlock(&philo->args->message);
}

int	destroy(t_args *args)
{
	int		i;

	i = -1;
	while (++i < args->nbr_of_philo)
	{
		if (pthread_mutex_destroy(&args->forks[i]) != SUCCESS)
			return (FAIL);
	}
	free(args->forks);
	if (pthread_mutex_destroy(&args->message) != SUCCESS)
		return (FAIL);
	if (pthread_mutex_destroy(&args->wait) != SUCCESS)
		return (FAIL);
	return (SUCCESS);
}
