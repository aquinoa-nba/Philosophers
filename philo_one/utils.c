/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 18:25:08 by aquinoa           #+#    #+#             */
/*   Updated: 2021/05/16 22:49:03 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

void	ft_putnbr_fd(unsigned long n, int fd)
{
	char	nbr;

	if (n >= 10)
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putnbr_fd(n % 10, fd);
	}
	else if (n < 10 && n >= 0)
	{
		nbr = n + 48;
		write(fd, &nbr, 1);
	}
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
	if (philo->args->dead)
	{
		time = what_time() - philo->args->start;
		ft_putnbr_fd(time, 1);
		write(1, "\t", 1);
		ft_putnbr_fd(philo->pos, 1);
		write(1, "\t", 1);
		write(1, str, ft_strlen(str));
	}
	pthread_mutex_unlock(&philo->args->message);
}
